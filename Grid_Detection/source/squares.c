#include "../include/squares.h"
#include "../../Tools/image.h"
#include <math.h>
#include <stdlib.h>

void sort_lines(int** lines, int len)
{
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (abs(lines[j][0]) > abs(lines[j + 1][0])) {
                int* temp = lines[j];
                lines[j] = lines[j + 1];
                lines[j + 1] = temp;
            }
        }
    }
}

double dist(int x0, int y0, int x1, int y1)
{
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

double max(double d1, double d2, double d3, double d4)
{
    double max = 0;

    if (d1 < d2)
        max = d2;
    else
        max = d1;

    if (d3 > max)
        max = d3;
    if (d4 > max)
        max = d4;

    return max;
}

double min(double d1, double d2, double d3, double d4)
{
    double min = 0;

    if (d1 < d2)
        min = d1;
    else
        min = d2;

    if (d3 < min)
        min = d3;
    if (d4 < min)
        min = d4;

    return min;
}

void render_line(Image *img, int x0, int y0, int x1, int y1, Pixel color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (1)
    {
        if (x0 >= 0 && x0 < (int) img->width
                && y0 >= 0 && y0 < (int) img->height)
            img->matrix[x0][y0] = color;

        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x0 == x1)
                break;
            error += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            if (y0 == y1)
                break;
            error += dx;
            y0 += sy;
        }
    }
}

Point get_intersection(int r1, int t1, int r2, int t2)
{
    int x = -1;
    int y = -1;
    double rad1 = t1 * M_PI / 180;
    double rad2 = t2 * M_PI / 180;
    double a1 = cos(rad1);
    double b1 = sin(rad1);
    double c1 = r1;
    double a2 = cos(rad2);
    double b2 = sin(rad2);
    double c2 = r2;

    double denominator = a1 * b2 - a2 * b1;

    if (denominator != 0)
    {
        x = round((b2 * c1 - b1 * c2) / denominator);
        y = round((a1 * c2 - a2 * c1) / denominator);
    }

    return (Point){x, y};
}

void get_squares(int hori_len, int verti_len,
                 int **hori_lines, int **verti_lines,
                 Square *squares)
{
    unsigned long m = 0;
    for (int i = 0; i < hori_len - 1; i++)
    {
        for (int j = 1; j < verti_len; j++)
        {
            for (int k = i + 1; k < hori_len; k++)
            {
                for (int l = 0; l < j; l++)
                {
                    Point p1 = get_intersection(
                            verti_lines[l][0], verti_lines[l][1], hori_lines[i][0],
                            hori_lines[i][1]);
                    Point p2 = get_intersection(
                            hori_lines[i][0], hori_lines[i][1], verti_lines[j][0],
                            verti_lines[j][1]);
                    Point p3 = get_intersection(
                            verti_lines[j][0], verti_lines[j][1], hori_lines[k][0],
                            hori_lines[k][1]);
                    Point p4 = get_intersection(
                            hori_lines[k][0], hori_lines[k][1], verti_lines[l][0],
                            verti_lines[l][1]);

                    if (p1.x < 0 || p1.y < 0 || p2.x < 0 || p2.y < 0
                            || p3.x < 0 || p3.y < 0 || p4.x < 0 || p4.y < 0)
                        continue;

                    squares[m] = (Square){p1, p2, p3, p4};
                    m++;
                }
            }
        }
    }
}

void draw_square(Image *img, Square square, Pixel color)
{
    for (int i = 0; i < 5; i++)
    {
        int x1 = square.p1.x - i;
        int y1 = square.p1.y - i;
        int x2 = square.p2.x - i;
        int y2 = square.p2.y - i;
        int x3 = square.p3.x - i;
        int y3 = square.p3.y - i;
        int x4 = square.p4.x - i;
        int y4 = square.p4.y - i;

        render_line(img, x1, y1, x2, y2, color);
        render_line(img, x2, y2, x3, y3, color);
        render_line(img, x3, y3, x4, y4, color);
        render_line(img, x4, y4, x1, y1, color);
    }
}

void draw_all_squares(Image *img, int nb_squares, Square *squares)
{
    for (int i = 0; i < nb_squares; i++)
    {
        if (squares[i].p1.x == nb_squares || squares[i].p1.y == nb_squares ||
            squares[i].p2.x == nb_squares || squares[i].p2.y == nb_squares ||
            squares[i].p3.x == nb_squares || squares[i].p3.y == nb_squares ||
            squares[i].p4.x == nb_squares || squares[i].p4.y == nb_squares)
            continue;

        draw_square(img, squares[i], (Pixel){0, 255, 0});
    }
}

Square *draw_grid_square(Image *img, int nb_squares, Square *squares,
                         Square *grid_square)
{
    Square *current = NULL;
    double best_factor = 0;

    for (int i = 0; i < nb_squares; i++)
    {
        current = &squares[i];
        if (current->p1.x == nb_squares || current->p1.y == nb_squares ||
            current->p2.x == nb_squares || current->p2.y == nb_squares ||
            current->p3.x == nb_squares || current->p3.y == nb_squares ||
            current->p4.x == nb_squares || current->p4.y == nb_squares)
            continue;

        double d1 =
            dist(current->p1.x, current->p1.y, current->p2.x, current->p2.y);
        double d2 =
            dist(current->p2.x, current->p2.y, current->p3.x, current->p3.y);
        double d3 =
            dist(current->p3.x, current->p3.y, current->p4.x, current->p4.y);
        double d4 =
            dist(current->p4.x, current->p4.y, current->p1.x, current->p1.y);

        double minimum = min(d1, d2, d3, d4);
        double maximum = max(d1, d2, d3, d4);

        double a1 = pow(minimum, 2);
        double a2 = pow(maximum, 2);

        double diff = a2 - a1;
        if (a2 == 0)
            continue;

        double factor = (diff / a2) * a1;
        double square_factor = a1 * 1.5 - factor * 3.5;

        if (square_factor >= best_factor)
        {
            best_factor = square_factor;
            grid_square = current;
        }
    }

    draw_square(img, *grid_square, (Pixel){0, 0, 255});
    return grid_square;
}

void squares(Image* img, unsigned int *lines_len, int ***real_lines, Square **squares, Square **gs, Image ***result_imgs)
{
    // Separate lines into 2 categories: horizontal and vertical lines
    int nb_hori_lines = 0;
    int nb_verti_lines = 0;

    for (unsigned int i = 0; i < *lines_len; i++)
    {
        if ((*real_lines)[i][2] == 1)
            nb_verti_lines++;
        if ((*real_lines)[i][2] == 2)
            nb_hori_lines++;
    }

    int **hori_lines = malloc(sizeof(int*) * nb_hori_lines);
    for (int i = 0; i < nb_hori_lines; i++)
        hori_lines[i] = malloc(sizeof(int) * 2);

    int **verti_lines = malloc(sizeof(int*) * nb_verti_lines);
    for (int i = 0; i < nb_verti_lines; i++)
        verti_lines[i] = malloc(sizeof(int) * 2);

    int diag = round(sqrt(pow(img->height, 2) + pow(img->width, 2)));
    unsigned int h = 0;
    unsigned int v = 0;
    for (unsigned int i = 0; i < *lines_len; i++) {
        if ((*real_lines)[i][2] == 1) {
            verti_lines[v][0] = (*real_lines)[i][0] - diag;
            verti_lines[v][1] = (*real_lines)[i][1];
            v++;
        }
        if ((*real_lines)[i][2] == 2) {
            hori_lines[h][0] = (*real_lines)[i][0] - diag;
            hori_lines[h][1] = (*real_lines)[i][1];
            h++;
        }
    }

    sort_lines(hori_lines, nb_hori_lines);
    sort_lines(verti_lines, nb_verti_lines);

    // Getting squares
    int nb_squares = pow((nb_hori_lines - 1), 2) * pow((nb_verti_lines - 1), 2);

    *squares = malloc(sizeof(Square) * nb_squares);
    for (int i = 0; i < nb_squares; i++)
    {
        (*squares)[i].p1 = (Point){nb_squares, nb_squares};
        (*squares)[i].p2 = (Point){nb_squares, nb_squares};
        (*squares)[i].p3 = (Point){nb_squares, nb_squares};
        (*squares)[i].p4 = (Point){nb_squares, nb_squares};
    }

    get_squares(nb_hori_lines, nb_verti_lines, hori_lines, verti_lines, *squares);

    draw_all_squares(img, nb_squares, *squares);

    // Storing image
    Image *tmp = malloc(sizeof(Image));
    copy_image(img, tmp);
    (*result_imgs)[2] = tmp;
    //save_image(img, "results/step_02_squares_detection.jpeg");

    // Getting main square
    *gs = draw_grid_square(img, nb_squares, *squares, *gs);

    // Storing image
    (*result_imgs)[3] = img;
    //save_image(img, "results/step_03_main_grid_detection.jpeg");

    // Freeing arrays
    for (int i = 0; i < nb_hori_lines; i++)
        free(hori_lines[i]);
    free(hori_lines);

    for (int i = 0; i < nb_verti_lines; i++)
        free(verti_lines[i]);
    free(verti_lines);
}


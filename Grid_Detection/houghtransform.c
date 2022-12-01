#include "houghtransform.h"
#include "../Images_Post_Grid/include/perspective_correction.h"
#include "../Images_Post_Grid/include/split_grid.h"
#include "../Tools/image.h"
#include "../Tools/rotate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int theta_val = 180;

int max_dist(Image *img)
{
    return round(sqrt(pow(img->height, 2) + pow(img->width, 2)));
}

void add_to_acc(unsigned int x, unsigned int y, int diag,
                int theta, unsigned int acc[])
{
    for (int t = 0; t < theta; t++)
    {
        double rad = t * M_PI / 180;
        double r = x * cos(rad) + y * sin(rad);
        int rho = r + diag;

        acc[rho * theta + t]++;
    }
}

unsigned int max_value(unsigned int len, unsigned int acc[])
{
    unsigned int max = 0;

    for (unsigned int i = 0; i < len; i++)
    {
        if (acc[i] > max)
            max = acc[i];
    }

    return max;
}

void draw_lines(Image *img, unsigned int len, int diag, int **lines)
{
    for (unsigned int i = 0; i < len; i++)
    {
        int r = lines[i][0];
        int t = lines[i][1];
        double rad = t * M_PI / 180;

        for (unsigned int x = 0; x < img->width; x++)
        {
            for (unsigned int y = 0; y < img->height; y++)
            {
                int eq = round((x * cos(rad) + y * sin(rad) + diag) - r);
                if (eq == 0)
                    img->matrix[x][y] = (Pixel) {255, 0, 0};
            }
        }
    }
}

void get_lines(int rho, int theta, unsigned int acc[],
               int **lines)
{
    double threshold = max_value(rho * theta, acc) * 0.5 + 50;

    int rho_min_dist = 20;
    int rho_vertical = 0;
    int rho_horizontal = 0;

    // unsigned int theta_min_angle = 5;
    // unsigned int theta_vertical = 90;
    // unsigned int theta_horizontal = 0;

    for (int t = 0; t < theta; t++)
    {
        for (int r = 0; r < rho; r++)
        {
            int i = r * theta + t;
            double rad = t * M_PI / 180;

            // Only drawing lines when it is a local maxima
            int is_local_max = 1;
            if (r > 0)
                is_local_max &= acc[(r - 1) * theta + t] <= acc[i];

            if (is_local_max && r + 1 < rho - 1)
                is_local_max &= acc[(r + 1) * theta + t] <= acc[i];

            if (is_local_max && t > 0)
                is_local_max &= acc[r * theta + (t - 1)] <= acc[i];

            if (is_local_max && t + 1 < theta - 1)
                is_local_max &= acc[r * theta + (t + 1)] <= acc[i];

            if (is_local_max && (double)acc[i] >= threshold)
            {
                // Filtering lines which are too close (rho)
                if (sin(rad) < 0.5)
                {
                    // Vertical Lines
                    if (abs((int)r - rho_vertical) > rho_min_dist)
                    {
                        rho_vertical = r;
                        lines[i][2] = 1;
                    }
                    else
                        continue;
                }
                else
                {
                    // Horizontal Lines
                    if (abs((int)r - rho_horizontal) > rho_min_dist)
                    {
                        rho_horizontal = r;
                        lines[i][2] = 2;
                    }
                    else
                        continue;
                }

                // Filtering lines with almost equal angles (theta)
                //if (sin(rad) < 0.5) {
                //    // Vertical Lines
                //    if (t - theta_vertical < theta_min_angle)
                //        continue;
                //} else {
                //    // Horizontal Lines
                //    if (t - theta_horizontal < theta_min_angle)
                //        continue;
                //}

                // if (t != 0 && t != 90 && t != 180)
                //     continue;

                lines[i][0] = r;
                lines[i][1] = t;
            }
            else
            {
                lines[i][0] = rho; // Impossible values
                lines[i][1] = theta;
            }
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

void render_line(Image *img, int x0, int y0, int x1, int y1, Pixel color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (1)
    {
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
        //printf("p1: (%d, %d) / p2: (%d, %d) / p3: (%d, %d) / p4: (%d, %d)\n", squares[i].p1.x, squares[i].p1.y, squares[i].p2.x, squares[i].p2.y, squares[i].p3.x, squares[i].p3.y, squares[i].p4.x, squares[i].p4.y);
        draw_square(img, squares[i], (Pixel){0, 255, 0});
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
        double square_factor = a1 * 2 - factor * 3.5;

        if (square_factor >= best_factor)
        {
            best_factor = square_factor;
            grid_square = current;
        }
    }

    draw_square(img, *grid_square, (Pixel){0, 0, 255});
    return grid_square;
}

/*
void get_all_intersections(unsigned int len, unsigned int diag,
        unsigned int** lines, Point* points) {
    unsigned int k = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (lines[i][2] == 1) {
            for (unsigned int j = 0; j < len; j++) {
                if (lines[j][2] == 2) {
                    Point p = get_intersection(lines[i][0], lines[i][1],
                            lines[j][0], lines[j][1], diag);

                    points[k] = p;
                    k++;
                }
            }
        }
    }
}

void draw_all_intersections(Image* img, unsigned int nb_points, Point* points) {
    for (unsigned int i = 0; i < nb_points; i++) {
        // Draw Intersection Points
        Point p = points[i];
        unsigned int x = p.x;
        unsigned int y = p.y;

        if ((x == nb_points && y == nb_points) || (x >= img->width || y >=
img->height)) continue;

        unsigned int size = 5;
        Point* neighbours = malloc(sizeof(Point) * size * size);
        _get_around_pixels(img, x, y, size, neighbours);

        for (unsigned int i = 0; i < size * size; i++) {
            unsigned int x = neighbours[i].x;
            unsigned int y = neighbours[i].y;

            if (x >= img->width || y >= img->height)
                continue;

            img->matrix[x][y] = (Pixel) {0, 255, 0};
        }

        //
        if (x > 0) {
            img->matrix[x - 1][y] = (Pixel) { 0, 255, 0 };
            if (y > 0)
                img->matrix[x - 1][y - 1] = (Pixel) { 0, 255, 0 };
        }

        if (x + 1 < img->width - 1) {
            img->matrix[x + 1][y] = (Pixel) { 0, 255, 0 };
            if (y + 1 < img->height - 1)
                img->matrix[x + 1][y + 1] = (Pixel) { 0, 255, 0 };

        }

        if (y > 0) {
            img->matrix[x][y - 1] = (Pixel) { 0, 255, 0 };
            if (x < img->width - 1)
                img->matrix[x + 1][y - 1] = (Pixel) { 0, 255, 0 };
        }

        if (y + 1 < img->height - 1) {
            img->matrix[x][y + 1] = (Pixel) { 0, 255, 0 };
            if (x > 0)
                img->matrix[x - 1][y + 1] = (Pixel) { 0, 255, 0 };
        }

        img->matrix[x][y] = (Pixel) { 0, 255, 0 };
    }
}

void draw_intersection(Image* img, unsigned int nb_points, Point p) {
    unsigned int x = p.x;
    unsigned int y = p.y;

    if ((x == nb_points && y == nb_points) || (x >= img->width || y >=
img->height)) return;

    unsigned int size = 5;
    Point* neighbours = malloc(sizeof(Point) * size * size);
    _get_around_pixels(img, x, y, size, neighbours);

    for (unsigned int i = 0; i < size * size; i++) {
        unsigned int x = neighbours[i].x;
        unsigned int y = neighbours[i].y;

        if (x >= img->width || y >= img->height)
            continue;

        img->matrix[x][y] = (Pixel) {0, 255, 0};
    }
}

void search_pattern(Image* img, unsigned int nb_points, Point* points) {
    unsigned int dist = 0;
    unsigned int min_dist = 58;
    Point next_point = points[0];
    for (unsigned int i = 0; i < nb_points - 1; i++) {
        next_point = points[i + 1];
        dist = sqrt(pow((int) next_point.x - (int) points[i].x, 2)
                + pow((int) next_point.y - (int) points[i].y, 2));

        if (dist != 0 && dist > min_dist)
            continue;

        draw_intersection(img, nb_points, points[i]);
    }
}
*/

void extract_cells(Image *img)
{
    Image **cells = malloc(81 * sizeof(Image *));
    get_cells(img, cells);
    char name[8] = "0i.jpeg";
    for (unsigned char i = 0; i < 81; i++)
    {
        if (i < 10)
            name[1] = i + '0';
        else
        {
            name[0] = i / 10 + '0';
            name[1] = i % 10 + '0';
        }
        save_image(cells[i], name);
        free_image(cells[i]);
        free(cells[i]);
    }
    free(cells);
}

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

int is_in_list(int *arr, unsigned int len, int element) {
    for (unsigned int i = 0; i < len; i++)
        if (arr[i] == element)
            return i;
    return -1;
}

int get_rotated_angle(int **lines, unsigned int len, int theta)
{
    int nb_thetas = len;
    int *total_thetas = malloc(sizeof(int) * nb_thetas);
    int *t_votes = malloc(sizeof(int) * nb_thetas);
    for (int i = 0; i < nb_thetas; i++)
        t_votes[i] = 0;

    int j = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        int in_list = is_in_list(total_thetas, nb_thetas, lines[i][1]);
        if (in_list == -1)
        {
            total_thetas[j] = lines[i][1];
            t_votes[j] = 1;
        }
        else
        {
            total_thetas[j] = theta;
            t_votes[in_list]++;
        }

        j++;
    }

    int max = 0;
    for (int i = 0; i < nb_thetas; i++)
    {
        if (t_votes[i] > max)
            max = i;
    }

    int angle = total_thetas[max];
    if (angle < 10 || abs(angle - 90) < 10 || abs(angle - 180) < 10)
        return 0;

    /*
    for (unsigned int i = 0; i < len; i++)
    {
            printf("t: %d / nt: %d\n", lines[i][1], lines[i][1] - angle);
            lines[i][1] -= angle;
            if (lines[i][1] >= 180)
                lines[i][1] -= 180;

            double rad = lines[i][1] * M_PI / 180;
            if (sin(rad) < 0.5)
            {
                // Vertical
                lines[i][2] = 1;
                lines[i][0] -= 332;
            }
            else
            {
                // Horizontal
                lines[i][2] = 2;
                lines[i][0] += 650;
            }
    }
    */

    return angle;
}

void hough_transform(Image *img, unsigned int *lines_len, int ***real_lines)
{
    // Initializing accumulator
    int diag = max_dist(img);
    int rho = 2 * diag;
    int theta = theta_val;
    unsigned int len = rho * theta;

    printf("%d * %d = %d\n", rho, theta, len);
    unsigned int accumulator[len];

    for (unsigned int i = 0; i < len; i++)
        accumulator[i] = 0;

    // Filling accumulator
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            if (img->matrix[x][y].r >= 250)
                add_to_acc(x, y, diag, theta, accumulator);
        }
    }

    // Initializing lines
    int **lines = malloc(sizeof(int*) * len);
    for (unsigned int i = 0; i < len; i++)
        lines[i] = malloc(sizeof(int) * 3);

    // Getting lines
    get_lines(rho, theta, accumulator, lines);

    // Eliminating false lines
    *lines_len = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        if (lines[i][0] == 0 && lines[i][1] == 0)
        {
            lines[i][0] = rho;
            lines[i][1] = theta;
        }

        if (lines[i][0] < rho && lines[i][1] < theta)
            (*lines_len)++;
    }

    // Reducing lines
    *real_lines = malloc(sizeof(int*) * (*lines_len));
    for (unsigned int i = 0; i < *lines_len; i++)
        (*real_lines)[i] = malloc(sizeof(int) * 3);

    unsigned int j = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        if (lines[i][0] < rho && lines[i][1] < theta)
        {
            (*real_lines)[j][0] = lines[i][0];
            (*real_lines)[j][1] = lines[i][1];
            (*real_lines)[j][2] = lines[i][2];
            j++;
        }
    }

    // Drawing lines
    draw_lines(img, *lines_len, diag, *real_lines);
}

void auto_rotation(Image *img, Image *copy_img, unsigned int *lines_len, int ***real_lines)
{
    // Auto rotating the image
    int theta = theta_val;
    int angle = get_rotated_angle(*real_lines, *lines_len, theta);

    if (angle != 0)
    {
        rotate(copy_img, -angle);

        hough_transform(copy_img, lines_len, real_lines);
        copy_image(copy_img, img);

        save_image(copy_img, "hough_rotated.jpeg");
        free_image(copy_img);
    }
}

void squares(Image* img, unsigned int *lines_len, int ***real_lines, Square **gs)
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

    int diag = max_dist(img);
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

    for (int i = 0; i < nb_hori_lines; i++) {
        printf("r: %d / t: %d / HORI\n", hori_lines[i][0], hori_lines[i][1]);
    }
    for (int i = 0; i < nb_verti_lines; i++) {
        printf("r: %d / t: %d / VERTI\n", verti_lines[i][0], verti_lines[i][1]);
    }

    sort_lines(hori_lines, nb_hori_lines);
    sort_lines(verti_lines, nb_verti_lines);

    // Getting squares
    int nb_squares = pow((nb_hori_lines - 1), 2) * pow((nb_verti_lines - 1), 2);

    Square *squares = malloc(sizeof(Square) * nb_squares);
    for (int i = 0; i < nb_squares; i++)
    {
        squares[i].p1 = (Point){nb_squares, nb_squares};
        squares[i].p2 = (Point){nb_squares, nb_squares};
        squares[i].p3 = (Point){nb_squares, nb_squares};
        squares[i].p4 = (Point){nb_squares, nb_squares};
    }

    get_squares(nb_hori_lines, nb_verti_lines, hori_lines, verti_lines, squares);

    draw_all_squares(img, nb_squares, squares);
    save_image(img, "squares_detection.jpeg");

    // Getting main square
    *gs = draw_grid_square(img, nb_squares, squares, *gs);
    save_image(img, "main_grid_detection.jpeg");
}

void perspective(Image *img, Square **gs)
{
    // Perspective correction
    int points[8] = { (*gs)->p1.x, (*gs)->p1.y, (*gs)->p2.x, (*gs)->p2.y,
        (*gs)->p3.x, (*gs)->p3.y, (*gs)->p4.x, (*gs)->p4.y };

    correct_perspective(img, points);

    // Extracting the 81 cells
    // extract_cells(img);
}

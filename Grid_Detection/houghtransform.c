#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Tools/image.h"
#include "houghtransform.h"

unsigned int max_dist(Image* img) {
    return round(sqrt(pow(img->height, 2) + pow(img->width, 2)));
}

void add_to_acc(unsigned int x, unsigned int y, unsigned int diag,
        unsigned int theta, unsigned int acc[]) {
    for (unsigned int t = 0; t < theta; t++) {
        double rad = t * M_PI / 180;
        double r = x * cos(rad) + y * sin(rad);
        unsigned int rho = r + diag;

        acc[rho * theta + t]++;
    }
}

unsigned int max_value(unsigned int len, unsigned int acc[]) {
    unsigned int max = 0;

    for (unsigned int i = 0; i < len; i++) {
        if (acc[i] > max)
            max = acc[i];
    }

    return max;
}

/*
void draw_lines(Image* img, unsigned int rho, double rad, unsigned int diag) {
    for (unsigned int x = 0; x < img->width; x++) {
        for (unsigned int y = 0; y < img->height; y++) {
            if ((int) round((x * cos(rad) + y * sin(rad) + diag) - rho) == 0) {
                //if (img->matrix[x][y].r >= 250)
                    img->matrix[x][y] = (Pixel) { 255, 0, 0 };
            }
        }
    }
}

void get_lines(Image* img, unsigned int rho, unsigned int theta, unsigned int diag, unsigned int acc[]) {
    double threshold = max_value(rho * theta, acc) * 0.4;
    //double threshold = 400;

    unsigned int rho_min_dist = 20;
    unsigned int rho_vertical = 0;
    unsigned int rho_horizontal = 0;

    //unsigned int theta_min_angle = 5;
    //unsigned int theta_vertical = 90;
    //unsigned int theta_horizontal = 0;

    for (unsigned int t = 0; t < theta; t++) {
        for (unsigned int r = 0; r < rho; r++) {
            unsigned int i = r * theta + t;
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

            if (is_local_max && (double) acc[i] >= threshold) {
                // Filtering lines which are too close (rho)
                if (sin(rad) > 0.5) {               // Vertical Lines
                    if (r - rho_vertical > rho_min_dist)
                        rho_vertical = r;
                    else
                        continue;
                } else {                            // Horizontal Lines
                    if (r - rho_horizontal > rho_min_dist)
                        rho_horizontal = r;
                    else
                        continue;
                }

                // Filtering lines with almost equal angles (theta)
                //if (sin(rad) > 0.5) {               // Vertical Lines
                //    if (t - theta_vertical < theta_min_angle)
                //        continue;
                //} else {                            // Horizontal Lines
                //    if (t - theta_horizontal < theta_min_angle)
                //        continue;
                //}

                draw_lines(img, r, rad, diag);
            }
        }
    }
}
*/

void draw_lines(Image* img, unsigned int rho, unsigned int theta,
        unsigned int diag, unsigned int** lines) {
    for (unsigned int i = 0; i < rho * theta; i++) {
        unsigned int r = lines[i][0];
        unsigned int t = lines[i][1];
        double rad = t * M_PI / 180;

        if (r < rho && t < theta) {
            for (unsigned int x = 0; x < img->width; x++) {
                for (unsigned int y = 0; y < img->height; y++) {
                    int eq = round((x * cos(rad) + y * sin(rad) + diag) - r);
                    if (eq == 0) {
                        //if (img->matrix[x][y].r >= 250)
                            img->matrix[x][y] = (Pixel) { 255, 0, 0 };
                    }
                }
            }
        }
    }
}

void get_lines(unsigned int rho, unsigned int theta, unsigned int acc[],
        unsigned int** lines) {
    double threshold = max_value(rho * theta, acc) * 0.4;
    //double threshold = 400;

    unsigned int rho_min_dist = 20;
    unsigned int rho_vertical = 0;
    unsigned int rho_horizontal = 0;

    //unsigned int theta_min_angle = 5;
    //unsigned int theta_vertical = 90;
    //unsigned int theta_horizontal = 0;

    for (unsigned int t = 0; t < theta; t++) {
        for (unsigned int r = 0; r < rho; r++) {
            unsigned int i = r * theta + t;
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

            if (is_local_max && (double) acc[i] >= threshold) {
                // Filtering lines which are too close (rho)
                if (sin(rad) > 0.5) {               // Vertical Lines
                    if (r - rho_vertical > rho_min_dist) {
                        rho_vertical = r;
                        lines[i][2] = 1;
                    } else
                        continue;
                } else {                            // Horizontal Lines
                    if (r - rho_horizontal > rho_min_dist) {
                        rho_horizontal = r;
                        lines[i][2] = 2;
                  } else
                        continue;
                }

                // Filtering lines with almost equal angles (theta)
                //if (sin(rad) > 0.5) {               // Vertical Lines
                //    if (t - theta_vertical < theta_min_angle)
                //        continue;
                //} else {                            // Horizontal Lines
                //    if (t - theta_horizontal < theta_min_angle)
                //        continue;
                //}

                lines[i][0] = r;
                lines[i][1] = t;
            } else {
                lines[i][0] = rho;
                lines[i][1] = theta;
            }
        }
    }
}

Point get_intersection(unsigned int r1, unsigned int t1, unsigned int r2,
        unsigned int t2, unsigned int diag) {
    unsigned int x = 0;
    unsigned int y = 0;
    double rad1 = t1 * M_PI / 180;
    double rad2 = t2 * M_PI / 180;
    double a1 = cos(rad1);
    double b1 = sin(rad1);
    double c1 = (int) diag - (int) r1;
    double a2 = cos(rad2);
    double b2 = sin(rad2);
    double c2 = (int) diag - (int) r2;

    double denominator = a1 * b2 - a2 * b1;

    if (denominator != 0) {
        x = round((b1 * c2 - b2 * c1) / denominator);
        y = round((a2 * c1 - a1 * c2) / denominator);
    }

    return (Point) { x, y };
}

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
        /* Draw Intersection Points */
        Point p = points[i];
        unsigned int x = p.x;
        unsigned int y = p.y;

        if (x == nb_points && y == nb_points)
            continue;

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

void hough_transform(Image* img) {
    unsigned int diag = max_dist(img);
    unsigned int rho = 2 * diag;
    unsigned int theta = 180;
    unsigned int len = rho * theta;

    printf("%d * %d = %d\n", rho, theta, len);
    unsigned int accumulator[len];

    for (unsigned int i = 0; i < len; i++) {
        accumulator[i] = 0;
    }

    for (unsigned int x = 0; x < img->width; x++) {
        for (unsigned int y = 0; y < img->height; y++) {
            if (img->matrix[x][y].r >= 250) {
                add_to_acc(x, y, diag, theta, accumulator);
            }
        }
    }

    unsigned int** lines = malloc(sizeof(unsigned int*) * len);
    for (unsigned int i = 0; i < len; i++) {
        lines[i] = malloc(sizeof(unsigned int) * 3);
    }

    get_lines(rho, theta, accumulator, lines);
    draw_lines(img, rho, theta, diag, lines);

    unsigned int nb_hori_lines = 0;
    unsigned int nb_verti_lines = 0;

    for (unsigned int i = 0; i < len; i++) {
        if (lines[i][0] < rho && lines[i][1] < theta) {
            if (lines[i][2] == 1)
                nb_verti_lines++;
            if (lines[i][2] == 2)
                nb_hori_lines++;
        }
    }

    unsigned int nb_points = nb_hori_lines * nb_verti_lines;
    Point* points = malloc(sizeof(Point) * nb_points);
    for (unsigned int i = 0; i < nb_points; i++) {
        points[i].x = nb_points;
        points[i].y = nb_points;
    }

    get_all_intersections(len, diag, lines, points);
    draw_all_intersections(img, nb_points, points);
    //get_lines(img, rho, theta, diag, accumulator);
}

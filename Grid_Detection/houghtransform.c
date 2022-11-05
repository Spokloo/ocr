#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Preprocessing/tools/image.h"

unsigned int max_dist(Image* img) {
    return round(sqrt(pow(img->height, 2) + pow(img->width, 2)));
}

void add_to_acc(unsigned int x, unsigned int y, unsigned int diag, unsigned int theta, unsigned int acc[]) {
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

                /*
                // Filtering lines with almost equal angles (theta)
                if (sin(rad) > 0.5) {               // Vertical Lines
                    if (t - theta_vertical < theta_min_angle)
                        continue;
                } else {                            // Horizontal Lines
                    if (t - theta_horizontal < theta_min_angle)
                        continue;
                }
                */

                draw_lines(img, r, rad, diag);
            }
        }
    }
}

/*
unsigned int** get_lines(unsigned int rho, unsigned int theta, unsigned int acc[]) {
    double threshold = max_value(rho * theta, acc) * 0.7;
    unsigned int** lines;
    lines = (unsigned int**) malloc(sizeof(unsigned int*) * (rho * theta));

    for (unsigned int r = 0; r < rho; r++) {
        for (unsigned int t = 0; t < theta; t++) {
            unsigned int i = r * theta + t;
            lines[i] = (unsigned int*) malloc(sizeof(unsigned int) * 2);

            if ((double) acc[i] >= threshold) {
                lines[i][0] = r;
                lines[i][1] = t;
            } else {
                lines[i][0] = rho;
                lines[i][1] = theta;
            }
        }
    }

    return lines;
}

void draw_lines(Image* img, unsigned int rho, unsigned int theta, unsigned int diag, unsigned int** lines) {
    for (unsigned int i = 0; i < rho * theta; i++) {
        unsigned int r = lines[i][0];
        unsigned int t = lines[i][1];
        double rad = t * M_PI / 180;

        if (r < rho && t < theta) {
            for (unsigned int x = 0; x < img->width; x++) {
                for (unsigned int y = 0; y < img->height; y++) {
                    if ((int) round((x * cos(rad) + y * sin(rad) + diag) - rho) == 0) {
                        img->matrix[x][y] = (Pixel) { 255, 0, 0 };
                    }
                }
            }
        }
    }
}
*/

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

    //unsigned int** lines = get_lines(rho, theta, accumulator);
    //draw_lines(img, rho, theta, diag, lines);
    get_lines(img, rho, theta, diag, accumulator);
}

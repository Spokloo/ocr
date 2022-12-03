#include "../include/houghtransform.h"
#include "../../Tools/image.h"
#include <math.h>
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
    double threshold = max_value(rho * theta, acc) * 0.5 + 55;

    int rho_min_dist = 20;
    int rho_vertical = 0;
    int rho_horizontal = 0;

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

void hough_transform(Image *img, unsigned int *lines_len, int ***real_lines)
{
    // Initializing accumulator
    int diag = max_dist(img);
    int rho = 2 * diag;
    int theta = theta_val;
    unsigned int len = rho * theta;

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
    {
        lines[i] = malloc(sizeof(int) * 3);
        for (unsigned int j = 0; j < 3; j++)
            lines[i][j] = 0;
    }

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
    {
        (*real_lines)[i] = malloc(sizeof(int) * 3);
        for (unsigned int j = 0; j < 3; j++)
            (*real_lines)[i][j] = 0;
    }

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

    // Freeing lines
    for (unsigned int i = 0; i < len; i++)
        free(lines[i]);
    free(lines);
}


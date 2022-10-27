#include <stdio.h>
#include <math.h>
#include "../Preprocessing/tools/image.h"

#define THETA 360



size_t max_dist(Image* img) {
    int w = img->width;
    int h = img->height;

    return (size_t) sqrt(w*w + h*h);
}

void add_to_acc(size_t len, size_t cols, int acc[], int x, int y) {
    for (size_t c = 0; c < cols; c++) {
        float rad = c * M_PI / 180;
        long rho = -(x * cos(rad)) + (y * sin(rad));
        if (rho >= 0 && rho * cols + c < len)
            acc[rho * cols + c] += 1;
    }
}

int max_val(int acc[], size_t len) {
    int max = 0;
    for (size_t i = 0; i < len; i++) {
        if (acc[i] > max)
            max = acc[i];
    }

    return max;
}

void draw_line(Image* img, size_t rho, size_t theta) {
    float rad = theta * M_PI / 180;
    for (unsigned int x = 0; x < img->width; x++) {
        for (unsigned int y = 0; y < img->height; y++) {
            long eq = x * cos(rad) - y * sin(rad) + rho;

            if (eq == 0) {
                img->matrix[x][y] = (Pixel) {255, 0, 0};
            }
        }
    }
}

void get_lines(Image* img, int acc[], size_t rows, size_t cols) {
    double threshold = max_val(acc, rows * cols) * 0.6;
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            size_t i = row * cols + col;
            if ((double) acc[i] >= threshold) {
                draw_line(img, row, col);
            }
        }
    }
}

void hough_transform(Image* img) {
    Pixel pixel;

    // Creating accumulator
    size_t rows = max_dist(img);
    size_t cols = THETA;
    size_t len = rows * cols;
    int accumulator[len];

    // Initializing accumulator
    for (size_t i = 0; i < len; i++) {
        accumulator[i] = 0;
    }

    // Adding to accumulator when a pixel is white
    for (unsigned int x = 0; x < img->width; x++) {
        for (unsigned int y = 0; y < img->height; y++) {
            pixel = img->matrix[x][y];
            if (pixel.r >= 250) {
                add_to_acc(len, cols, accumulator, x, y);
            }
        }
    }

    get_lines(img, accumulator, rows, cols);
}


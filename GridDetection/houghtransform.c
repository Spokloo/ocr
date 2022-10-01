#include <stdio.h>
#include <math.h>
#include "../Preprocessing/tools/image.h"

#define THETA 180



size_t max_dist(Image* img) {
    int x1 = 0;
    int y1 = 0;
    int x2 = img->width - 1;
    int y2 = img->height - 1;

    return (size_t) sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void add_to_acc(size_t len, size_t cols, int acc[], int x, int y) {
    for (size_t c = 0; c < cols; c++) {
        size_t rho = (y * cos(c)) - (x * sin(c));
        if (rho * cols + c < len)
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
    for (unsigned int x = 0; x < img->height; x++) {
        for (unsigned int y = 0; y < img->width; y++) {
            size_t eq = x * sin(theta) - y * cos(theta) + rho;

            if (eq == 0) {
                img->matrix[y][x] = (Pixel) {255, 0, 0};
            }
        }
    }
}

void get_lines(Image* img, int acc[], size_t rows, size_t cols) {
    int threshold = max_val(acc, rows * cols) * 0.7;
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            size_t i = row * cols + col;
            if (acc[i] >= threshold) {
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
    for (unsigned int x = 0; x < img->height; x++) {
        for (unsigned int y = 0; y < img->width; y++) {
            pixel = img->matrix[y][x];
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255) {
                add_to_acc(len, cols, accumulator, x, y);
            }
        }
    }

    get_lines(img, accumulator, rows, cols);
}


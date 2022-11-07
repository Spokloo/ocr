#ifndef HOUGH_TRANSFO
#define HOUGH_TRANSFO

#include "../Tools/image.h"

typedef struct Point {
    unsigned int x, y;
} Point;

typedef struct Line {
    unsigned int rho, theta;
} Line;

typedef struct Square {
    unsigned int x1, x2, x3, x4;
} Square;



void hough_transform(Image* img);

#endif

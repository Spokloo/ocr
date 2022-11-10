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
    Point p1, p2, p3, p4;
} Square;



void hough_transform(Image* img, double threshold);

#endif

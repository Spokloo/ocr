#ifndef HOUGH_TRANSFO
#define HOUGH_TRANSFO

#include "../Tools/image.h"

typedef struct Point
{
    int x, y;
} Point;

typedef struct Line
{
    unsigned int rho, theta;
} Line;

typedef struct Square
{
    Point p1, p2, p3, p4;
} Square;

void hough_transform(Image *img, unsigned int *lines_len, int ***real_lines);
void auto_rotation(Image *img, Image *copy_img, unsigned int *lines_len, int ***real_lines);
void squares(Image *img, unsigned int *lines_len, int ***real_lines, Square **gs);
void perspective(Image *img, Square **gs);

#endif

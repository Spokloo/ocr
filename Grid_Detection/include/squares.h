#ifndef SQUARES
#define SQUARES

#include "../../Tools/image.h"

typedef struct Point
{
    int x, y;
} Point;

typedef struct Square
{
    Point p1, p2, p3, p4;
} Square;

void squares(Image *img, unsigned int *lines_len, int ***real_lines, Square **gs, Image ***result_imgs);

#endif

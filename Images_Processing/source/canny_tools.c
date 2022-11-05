#include "../include/canny_tools.h"
#include "../../Tools/image.h"
#include <math.h>

/*
 * Normalize and convert gradient direction into degrees.
 * Return 0, 45, 90 or 135.
 */
unsigned int normalize_grad_dir(float dir)
{
    dir = 180 * dir / M_PI; // Convert in degrees
    if (dir < 0)
        dir += 180;
    if (dir >= 22.5 && dir < 67.5)
        return 45;
    if (dir >= 67.5 && dir < 112.5)
        return 90;
    if (dir >= 112.5 && dir < 157.5)
        return 135;
    return 0;
}

/*
 * Fill neighbours array with pixels values of neighbours at (x,y) depending on
 * gradient direction.
 * neighbours[0] and neighbours[1] for red
 * neighbours[2] and neighbours[3] for green
 * neighbours[4] and neighbours[5] for blue
 * Consider that x and y are always correct.
 */
void get_grad_neighbours(unsigned int grad_dir, Image *img,
                    unsigned int x, unsigned int y, unsigned int *neighbours)
{
    switch (grad_dir)
    {
    case 0:
        neighbours[0] = img->matrix[x][y - 1].r;
        neighbours[1] = img->matrix[x][y + 1].r;
        break;

    case 45:
        neighbours[0] = img->matrix[x -1][y + 1].r;
        neighbours[1] = img->matrix[x + 1][y - 1].r;
        break;

    case 90:
        neighbours[0] = img->matrix[x - 1][y].r;
        neighbours[1] = img->matrix[x + 1][y].r;
        break;

    case 135:
        neighbours[0] = img->matrix[x - 1][y - 1].r;
        neighbours[1] = img->matrix[x + 1][y + 1].r;
        break;
    }
}
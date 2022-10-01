#include "canny_tools.h"
#include "../tools/image.h"
#include <math.h>

/*
 * Compute the convolution product. Not a matrix product!
 */
unsigned int convolution_product(Pixel *pixels, float kernel[9],
                                 unsigned char color)
{
    float res = 0;
    unsigned int j = 8;
    switch (color)
    {
    case 'r':
        for (unsigned int i = 0; i < 9; i++)
        {
            res += pixels[j].r * kernel[i];
            j--;
        }
        break;

    case 'g':
        for (unsigned int i = 0; i < 9; i++)
        {
            res += pixels[j].g * kernel[i];
            j--;
        }
        break;

    case 'b':
        for (unsigned int i = 0; i < 9; i++)
        {
            res += pixels[j].b * kernel[i];
            j--;
        }
        break;
    }
    return (unsigned int)res;
}

/*
 * Normalize and convert gradient direction into degrees.
 * Return 0, 45, 90 or 135.
 */
unsigned int normalize_gradient_direction(float dir)
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
 */
void get_gradient_neighbours(Pixel **gradients_dirs, Pixel **matrix,
                    unsigned int x, unsigned int y, unsigned int *neighbours)
{
    //Red
    switch (gradients_dirs[x][y].r)
    {
    case 0:
        neighbours[0] = matrix[x][y - 1].r;
        neighbours[1] = matrix[x][y + 1].r;
        break;

    case 45:
        neighbours[0] = matrix[x - 1][y + 1].r;
        neighbours[1] = matrix[x + 1][y - 1].r;
        break;

    case 90:
        neighbours[0] = matrix[x - 1][y].r;
        neighbours[1] = matrix[x + 1][y].r;
        break;

    case 135:
        neighbours[0] = matrix[x - 1][y - 1].r;
        neighbours[1] = matrix[x + 1][y + 1].r;
        break;
    }

    //Green
    switch (gradients_dirs[x][y].g)
    {
    case 0:
        neighbours[2] = matrix[x][y - 1].g;
        neighbours[3] = matrix[x][y + 1].g;
        break;

    case 45:
        neighbours[2] = matrix[x - 1][y + 1].g;
        neighbours[3] = matrix[x + 1][y - 1].g;
        break;

    case 90:
        neighbours[2] = matrix[x - 1][y].g;
        neighbours[3] = matrix[x + 1][y].g;
        break;

    case 135:
        neighbours[2] = matrix[x - 1][y - 1].g;
        neighbours[3] = matrix[x + 1][y + 1].g;
        break;
    }

    //Blue
    switch (gradients_dirs[x][y].b)
    {
    case 0:
        neighbours[4] = matrix[x][y - 1].b;
        neighbours[5] = matrix[x][y + 1].b;
        break;

    case 45:
        neighbours[4] = matrix[x - 1][y + 1].b;
        neighbours[5] = matrix[x + 1][y - 1].b;
        break;

    case 90:
        neighbours[4] = matrix[x - 1][y].b;
        neighbours[5] = matrix[x + 1][y].b;
        break;

    case 135:
        neighbours[4] = matrix[x - 1][y - 1].b;
        neighbours[5] = matrix[x + 1][y + 1].b;
        break;
    }
}
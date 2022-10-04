#include "canny_tools.h"
#include "../tools/image.h"
#include <math.h>

/*
 * Compute the convolution product. Not a matrix product!
 */
double convolution_product(Pixel *pixels, double *kernel,
                                 unsigned char size, unsigned char color)
{
    double res = 0;
    unsigned int j = size-1;
    switch (color)
    {
    case 'r':
        for (unsigned char i = 0; i < size; i++)
        {
            res += ((double) pixels[j].r) * kernel[i];
            j--;
        }
        break;

    case 'g':
        for (unsigned char i = 0; i < size; i++)
        {
            res += ((double) pixels[j].g) * kernel[i];
            j--;
        }
        break;

    case 'b':
        for (unsigned char i = 0; i < size; i++)
        {
            res += ((double) pixels[j].b) * kernel[i];
            j--;
        }
        break;
    }
    return res;
}

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
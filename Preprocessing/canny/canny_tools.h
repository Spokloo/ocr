#ifndef CANNY_TOOLS_H
#define CANNY_TOOLS_H

#include "../tools/image.h"

/*
 * Compute the convolution product. Not a matrix product!
 */
double convolution_product(Pixel *pixels, double *kernel,
                                 unsigned char size, unsigned char color);

/*
 * Normalize and convert gradient direction into degrees.
 * Return 0, 45, 90 or 135.
 */
unsigned int normalize_grad_dir(float dir);

/*
 * Fill neighbours array with pixels values of neighbours at (x,y) depending on
 * gradient direction.
 * neighbours[0] and neighbours[1] for red
 * neighbours[2] and neighbours[3] for green
 * neighbours[4] and neighbours[5] for blue
 * Consider that x and y are always correct.
 */
void get_grad_neighbours(unsigned int grad_dir, Image *img,
                    unsigned int x, unsigned int y, unsigned int *neighbours);

#endif
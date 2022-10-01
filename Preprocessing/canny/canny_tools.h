#ifndef CANNY_TOOLS_H
#define CANNY_TOOLS_H

#include "../tools/image.h"

/*
 * Compute the convolution product. Not a matrix product!
 */
unsigned int convolution_product(Pixel *pixels, float kernel[9],
                                 unsigned char color);

/*
 * Normalize and convert gradient direction into degrees.
 * Return 0, 45, 90 or 135.
 */
unsigned int normalize_gradient_direction(float dir);

/*
 * Fill neighbours array with pixels values of neighbours at (x,y) depending on
 * gradient direction.
 * neighbours[0] and neighbours[1] for red
 * neighbours[2] and neighbours[3] for green
 * neighbours[4] and neighbours[5] for blue
 */
void get_gradient_neighbours(Pixel **gradients_dirs, Pixel **matrix,
                    unsigned int x, unsigned int y, unsigned int *neighbours);
#endif
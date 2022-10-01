#ifndef CANNY_H
#define CANNY_H

#include "../tools/image.h"

/*
 * Applying a blur with a convolution matrix.
 */
void blur(Image *img);

/*
 * Applying the Sobel filter (edge detection).
 * Return the matrix of normalized gradient direction.
 */
Pixel **sobel(Image *img);

/*
 * Removal of non-maximums: remove all "weak" values by following the angle of 
 * their gradient.
 */
void non_maximum_suppression(Image *img, Pixel **gradients_dirs);

#endif
#ifndef CANNY_H
#define CANNY_H

#include "../../Tools/image.h"

/*
 * Applying the Sobel filter (edge detection).
 * Return the matrix of normalized gradient direction.
 */
unsigned int **sobel(Image *img);

/*
 * Removal of non-maximums: remove all "weak" values by following the angle of
 * their gradient.
 */
unsigned int **non_maximum_suppression(Image *img, unsigned int **grad_dirs);

/*
 * Binarize the image to only have black or white pixels.
 * Pixels under tl are black. Pixels under th are white.
 * Pixels between tl and th depend on neighboors.
 */
void threashold(Image *img, unsigned int **grad_dirs, unsigned int tl,
                unsigned int th);

/*
 * Compute high threashold thanks to Otsu Algorithm.
 */
unsigned int compute_high_threashold(Image *img);

/*
 * Apply the canny filter.
 * (Sobel, Non-Maximum Suppression and Double Threashold)
 */
void canny(Image *img);

#endif
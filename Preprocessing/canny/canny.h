#ifndef CANNY_H
#define CANNY_H

#include "../tools/image.h"

/*
 * Applying a blur with a convolution matrix.
 */
void blur(Image *img);

/*
 * Applying the Sobel filter (edge detection).
 */
void sobel(Image *img);

#endif
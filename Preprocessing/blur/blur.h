#ifndef BLUR_H
#define BLUR_H

#include "../tools/image.h"

/*
 * Applying a blur with a convolution matrix.
 */
void gaussian_blur(Image *img, unsigned char filter_size);

/*
 * Median blur.
 */
void median_blur(Image *img);

#endif
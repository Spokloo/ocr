#ifndef BLUR_H
#define BLUR_H

#include "image.h"
#include "image_tools.h"

/*
 * Applying a gaussian blur with a convolution matrix.
 * Only on a grayscale image.
 */
void gaussian_blur(Image *img, unsigned char filter_size);

#endif
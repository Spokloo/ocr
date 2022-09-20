#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "../tools/image.h"

/*
 * Applying a convolution in img depending of filter matrix in parameters.
 */
void convolution(Image *img, float kernel[9]);

#endif
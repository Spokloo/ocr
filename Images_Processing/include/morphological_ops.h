#ifndef MORPHOLOGICAL_OPS_H
#define MORPHOLOGICAL_OPS_H

#include "../../Tools/image.h"

/*
 * Expand shapes in image.
 */
void dilation(Image *img, unsigned char filter_size);

/*
 * Reduce shapes in image.
 */
void erosion(Image *img, unsigned char filter_size);

#endif
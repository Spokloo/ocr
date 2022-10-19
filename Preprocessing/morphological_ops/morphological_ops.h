#ifndef MORPHOLOGICAL_OPS_H
#define MORPHOLOGICAL_OPS_H

#include "../tools/image.h"

/*
 * Expand white shapes in image.
 */
void dilation(Image *img);

/*
 * Reduce white shapes in image.
 */
void erosion(Image *img);

#endif
#ifndef PERSP_CORRECT_H
#define PERSP_CORRECT_H

#include "image.h"

/*
 * Correct perspective on image depending on grid position in src.
 */
void correct_perspective(Image *img, int dst[8]);

#endif
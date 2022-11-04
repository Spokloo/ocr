#ifndef PERSP_CORRECT
#define PERSP_CORRECT

#include "../tools/image.h"

/*
 * Correct perspective on image depending on grid position in src.
 */
void correct_perspective(Image *img, int dst[8]);

#endif
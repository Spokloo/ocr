#ifndef HOUGH_TRANSFO
#define HOUGH_TRANSFO

#include "../../Tools/image.h"

void hough_transform(Image *img, unsigned int *lines_len, int ***real_lines, Image ***result_imgs);

#endif

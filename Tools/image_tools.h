#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

#include "image.h"

/*
 * Getting the w*w pixels values around the pixel at (x,y) and put them
 * into around_pixels list.
 * Out of bound of matrix isn't manage!
 */
void get_around_pixels(Image *matrix, unsigned int x, unsigned int y, 
                                    unsigned char w, Pixel *around_pixels);

/*
 * Compute the convolution product on red pixels. Not a matrix product!
 */
float convolution_product(Pixel *pixels, float *kernel, unsigned char size);



#endif
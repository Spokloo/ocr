#ifndef ROTATE_H
#define ROTATE_H

#include "../tools/image.h"

/*
 * [SDL Library] Rotate the image with the given angle in degrees.
 */
void rotateSDL(char *img_path, int angle);

/*
 * Rotate the image with the given angle in degrees.
 */
void rotate(Image *img, short angle_deg);

#endif
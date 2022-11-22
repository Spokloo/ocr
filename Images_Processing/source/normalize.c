#include "../include/normalize.h"
#include "../../Tools/image.h"

/*
 * Normalize image luminosity between 0 and 255.
 */
void normalize(Image *img)
{

    float tmp = 0, max = 0, min = 0;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            tmp = img->matrix[x][y].r;
            if (tmp > max)
                max = tmp;
            if (tmp < min)
                min = tmp;
        }
    }

    float diff = 255 / (max - min);
    float newval = 0;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            newval = (img->matrix[x][y].r - min) * diff;
            img->matrix[x][y] = (Pixel){newval, newval, newval};
        }
    }
}
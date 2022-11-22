#include "../include/grayscale.h"
#include "../../Tools/image.h"

/*
 * Apply grayscale filter into image.
 */
void grayscale(Image *img)
{

    Pixel pixel;
    unsigned int average = 0;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            // Apply a formula on each pixel to remove colors
            pixel = img->matrix[x][y];
            average = 0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b;
            img->matrix[x][y] = (Pixel){average, average, average};
        }
    }
}

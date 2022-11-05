#include "../include/contrast.h"
#include "../../Tools/image.h"

/*
 * Truncate val between 0 and 255 (RGB range).
 */
unsigned int truncate(int val){
    if (val < 0)
        return 0;
    if (val > 255)
        return 255;
    return (unsigned int) val;
}

/*
 * Increase or decrease contrast of the image depending on level.
 */
void contrast(Image *img, int level){

    Pixel pixel;
    float factor = (259 * ((float) level + 255)) /
                                            (255 * (259 - (float)level));

    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            //Apply a formula on each pixel and each color to amplify contrast
            pixel = img->matrix[x][y];
            img->matrix[x][y].r =
                        truncate(factor * ((int) pixel.r - 128) + 128);
            img->matrix[x][y].g =
                        truncate(factor * ((int) pixel.g - 128) + 128);
            img->matrix[x][y].b =
                        truncate(factor * ((int) pixel.b - 128) + 128);
        }
    }
}

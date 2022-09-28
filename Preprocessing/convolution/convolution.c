#include "convolution.h"
#include "../tools/image.h"
#include <stdlib.h>

/*
 * Compute the convolution product. Not a matrix product!
 */
unsigned int convolution_product(Pixel *pixels, float kernel[9],
                                                        unsigned char color)
{
    float res = 0;
    switch (color)
    {
        case 'r':
            for(unsigned int i = 0; i < 9; i++)
                res += pixels[i].r * kernel[i];
            break;
        
        case 'g':
            for(unsigned int i = 0; i < 9; i++)
                res += pixels[i].g * kernel[i];
            break;

        case 'b':
            for(unsigned int i = 0; i < 9; i++)
                res += pixels[i].b * kernel[i];
            break;
    }
    return (unsigned int) res;    
}

/*
 * Applying a convolution in img depending of filter matrix in parameters.
 */
void convolution(Image *img, float kernel[9])
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel *around_pixels = malloc(9 * sizeof(Pixel));

    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            //Get 8 pixels around (x,y) and pixel at (x,y)
            get_around_pixels(original_image.matrix, x, y, 3, around_pixels);

            //Red
            img->matrix[x][y].r = convolution_product(around_pixels, kernel, 'r');
            //Green
            img->matrix[x][y].g = convolution_product(around_pixels, kernel, 'g');
            //Blue
            img->matrix[x][y].b = convolution_product(around_pixels, kernel, 'b');
        }
    }
    free(around_pixels);
    free_image(&original_image);
}

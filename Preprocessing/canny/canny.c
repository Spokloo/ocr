#include "canny.h"
#include "../tools/image.h"
#include <stdlib.h>
#include <math.h>

/*
 * Compute the convolution product. Not a matrix product!
 */
unsigned int convolution_product(Pixel *pixels, float kernel[9],
                                                        unsigned char color)
{
    float res = 0;
    unsigned int j = 8;
    switch (color)
    {
        case 'r':
            for(unsigned int i = 0; i < 9; i++)
            {
                res += pixels[j].r * kernel[i];
                j--;
            }                
            break;
        
        case 'g':
            for(unsigned int i = 0; i < 9; i++)
            {
                res += pixels[j].g * kernel[i];
                j--;
            }
            break;

        case 'b':
            for(unsigned int i = 0; i < 9; i++)
            {
                res += pixels[j].b * kernel[i];
                j--;
            }
            break;
    }
    return (unsigned int) res;    
}

/*
 * Applying a blur with a convolution matrix.
 */
void blur(Image *img)
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel *around_pixels = malloc(9 * sizeof(Pixel));
    //float kernel[9] = {0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11}; //filtre lisseur
    float kernel[9] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625}; //flou gaussien

    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            //Get 8 pixels around (x,y) and current pixel
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

/*
 * Applying the Sobel filter (edge detection).
 */
void sobel(Image *img)
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel *around_pixels = malloc(9 * sizeof(Pixel));

    unsigned int gxr, gxg, gxb, gyr, gyg, gyb;
    float kernel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    float kernel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    
    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            //Get 8 pixels around (x,y) and current pixel
            get_around_pixels(original_image.matrix, x, y, 3, around_pixels);

            //Red
            gxr = convolution_product(around_pixels, kernel_x, 'r');
            gyr = convolution_product(around_pixels, kernel_y, 'r');
            img->matrix[x][y].r = sqrt(gxr*gxr + gyr*gyr);

            //Green
            gxg = convolution_product(around_pixels, kernel_x, 'g');
            gyg = convolution_product(around_pixels, kernel_y, 'g');
            img->matrix[x][y].g = sqrt(gxg*gxg + gyg*gyg);

            //Blue
            gxb = convolution_product(around_pixels, kernel_x, 'b');
            gyb = convolution_product(around_pixels, kernel_y, 'b');
            img->matrix[x][y].b = sqrt(gxb*gxb + gyb*gyb);
        }
    }
    free(around_pixels);
    free_image(&original_image);
}
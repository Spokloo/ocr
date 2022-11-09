#include "../include/blur.h"
#include "../../Tools/image.h"
#include "../../Tools/image_tools.h"

/*
 * Applying a gaussian blur with a convolution matrix.
 * Only on a grayscale image.
 */
void gaussian_blur(Image *img, unsigned char filter_size)
{
    //Apply blur one or more time depend on filter_size
    float kernel[9] = 
           {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
    Pixel around_pixels[9];
    Image original_image;
    float tmp = 0;
    unsigned int x = 0, y = 0;
    for(unsigned char nb = filter_size / 3; nb > 0; nb--)
    {
        copy_image(img, &original_image);

        for(x = 1; x < img->width-1; x++)
        {
            for(y = 1; y < img->height-1; y++)
            {
                //Get pixels around (x,y) and the current pixel
                get_around_pixels(&original_image, x, y, 
                                        3, (Pixel*) &around_pixels);
                //Apply the convolution product
                tmp = convolution_product(around_pixels, (float*) &kernel, 9);
                img->matrix[x][y] = (Pixel) {tmp, tmp, tmp};
            }
        }

        free_image(&original_image);
    }    
}
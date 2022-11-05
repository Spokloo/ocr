#include "../include/morphological_ops.h"
#include "../../Tools/image.h"
#include "../../Tools/image_tools.h"

/*
 * Expand shapes in image.
 */
void dilation(Image *img, unsigned char filter_size)
{
    Image original_img;
    copy_image(img, &original_img);
    unsigned int min;
    Pixel around_pixels[filter_size*filter_size];
    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            min = 255;
            get_around_pixels(&original_img, x, y, filter_size, 
                                                    (Pixel*) &around_pixels);
            for(unsigned int k = 0; k < filter_size*filter_size; k++)
            {
                if (around_pixels[k].r < min)
                    min = around_pixels[k].r;
            }
            img->matrix[x][y] = (Pixel) {min, min, min};
        }
    }
    free_image(&original_img);
}

/*
 * Reduce shapes in image.
 */
void erosion(Image *img, unsigned char filter_size)
{
    Image original_img;
    copy_image(img, &original_img);
    unsigned int max;
    Pixel around_pixels[filter_size*filter_size];
    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            max = 0;
            get_around_pixels(&original_img, x, y, filter_size, 
                                                    (Pixel*) &around_pixels);
            for(unsigned int k = 0; k < filter_size*filter_size; k++)
            {
                if (around_pixels[k].r > max)
                    max = around_pixels[k].r;
            }
            img->matrix[x][y] = (Pixel) {max, max, max};
        }
    }
    free_image(&original_img);
}
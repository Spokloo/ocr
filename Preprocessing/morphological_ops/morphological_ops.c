#include "../tools/image.h"
#include "morphological_ops.h"

/*
 * Expand white shapes in image.
 */
void dilation(Image *img)
{
    Image original_img;
    copy_image(img, &original_img);
    unsigned int min;
    unsigned char size = 5;
    Pixel around_pixels[size*size];
    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            min = 255;
            get_around_pixels(&original_img, x, y, size, (Pixel*) &around_pixels);
            for(unsigned int k = 0; k < size*size; k++)
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
 * Reduce white shapes in image.
 */
void erosion(Image *img)
{
    Image original_img;
    copy_image(img, &original_img);
    unsigned int max;
    unsigned char size = 5;
    Pixel around_pixels[size*size];
    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            max = 0;
            get_around_pixels(&original_img, x, y, size, (Pixel*) &around_pixels);
            for(unsigned int k = 0; k < size*size; k++)
            {
                if (around_pixels[k].r > max)
                    max = around_pixels[k].r;
            }
            img->matrix[x][y] = (Pixel) {max, max, max};
        }
    }
    free_image(&original_img);
}
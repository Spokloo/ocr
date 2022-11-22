#include "image_tools.h"
#include "image.h"

/*
 * Getting the w*w pixels values around the pixel at (x,y) and put them
 * into around_pixels list.
 * Out of bound of matrix isn't manage!
 */
void get_around_pixels(Image *img, unsigned int x, unsigned int y,
                       unsigned char w, Pixel *around_pixels)
{
    // for odd numbers
    unsigned char fix = 0;
    unsigned char index = 0;
    if (w % 2 != 0)
        fix = 1;

    for (int i = x - w / 2; i < (int)(x + w / 2 + fix); i++)
    {
        for (int j = y - w / 2; j < (int)(y + w / 2 + fix); j++)
        {
            around_pixels[index] = img->matrix[i][j];
            index++;
        }
    }
}

/*
 * Compute the convolution product on red pixels. Not a matrix product!
 */
float convolution_product(Pixel *pixels, float *kernel, unsigned char size)
{
    float res = 0;
    unsigned int j = size - 1;
    for (unsigned char i = 0; i < size; i++)
    {
        res += ((float)pixels[j].r) * kernel[i];
        j--;
    }
    return res;
}
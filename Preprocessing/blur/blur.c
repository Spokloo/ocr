#include "../tools/image.h"
#include "blur.h"
#include <math.h>

/*
 * Applying a blur with a convolution matrix.
 */
void gaussian_blur(Image *img, unsigned char filter_size)
{
    //Apply one or more time depend on image_size
    unsigned char nb = filter_size / 3;
    for(; nb > 0; nb--)
    {
        Image original_image;
        copy_image(img, &original_image);
    
        float kernel[9] = 
           {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
        Pixel around_pixels[9];

        for(unsigned int x = 0; x < img->width; x++)
        {
            for(unsigned int y = 0; y < img->height; y++)
            {
                //Get pixels around (x,y) and the current pixel
                get_around_pixels(&original_image, x, y, 
                                        3, (Pixel*) &around_pixels);

                //Red
                img->matrix[x][y].r = 
                    convolution_product(around_pixels, (float*) &kernel, 9, 'r');
                //Green
                img->matrix[x][y].g = 
                    convolution_product(around_pixels, (float*) &kernel, 9, 'g');
                //Blue
                img->matrix[x][y].b = 
                    convolution_product(around_pixels, (float*) &kernel, 9, 'b');
            }
        }
        free_image(&original_image);
    }    
}

void insert_sort(Pixel *arr, int n)
{
    int i, j;
    unsigned int key;
    for (i = 1; i < n; i++) {
        key = arr[i].r;
        j = i - 1;
        while (j >= 0 && arr[j].r > key) {
            arr[j + 1].r = arr[j].r;
            j = j - 1;
        }
        arr[j + 1].r = key;
    }
}

void median_blur(Image *img)
{
    Image original_img;
    copy_image(img, &original_img);
    unsigned char size = 5;
    Pixel around_pixels[size*size];
    unsigned int new_val = 0;
    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            get_around_pixels(&original_img, x, y, size, (Pixel*) &around_pixels);
            insert_sort((Pixel*) &around_pixels, size*size);
            new_val = around_pixels[(size*size)/2].r;
            img->matrix[x][y] = (Pixel) {new_val, new_val, new_val};
        }
    }
    free_image(&original_img);
}
#include "canny.h"
#include "canny_tools.h"
#include "../tools/image.h"
#include <stdlib.h>
#include <math.h>

/*
 * Applying a blur with a convolution matrix.
 */
void blur(Image *img)
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel *around_pixels = malloc(9 * sizeof(Pixel));
    //flou gaussien
    float kernel[9] = 
            {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};

    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            //Get 8 pixels around (x,y) and current pixel
            get_around_pixels(original_image.matrix, x, y, 3, around_pixels);

            //Red
            img->matrix[x][y].r = 
                                convolution_product(around_pixels, kernel, 'r');
            //Green
            img->matrix[x][y].g = 
                                convolution_product(around_pixels, kernel, 'g');
            //Blue
            img->matrix[x][y].b = 
                                convolution_product(around_pixels, kernel, 'b');
        }
    }
    free(around_pixels);
    free_image(&original_image);
}

/*
 * Applying the Sobel filter (edge detection).
 * Return the matrix of normalized gradient direction.
 */
Pixel **sobel(Image *img)
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel *around_pixels = malloc(9 * sizeof(Pixel));
    Pixel **gradients_dirs = malloc(img->width * sizeof(Pixel*));

    unsigned int gxr, gxg, gxb, gyr, gyg, gyb;
    float kernel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    float kernel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    
    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        gradients_dirs[x] = malloc(img->height * sizeof(Pixel));
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            //Get 8 pixels around (x,y) and current pixel
            get_around_pixels(original_image.matrix, x, y, 3, around_pixels);

            //Red
            gxr = convolution_product(around_pixels, kernel_x, 'r');
            gyr = convolution_product(around_pixels, kernel_y, 'r');
            img->matrix[x][y].r = sqrt(gxr*gxr + gyr*gyr);
            gradients_dirs[x][y].r = normalize_gradient_direction(
                                                            atan2(gxr, gyr));

            //Green
            gxg = convolution_product(around_pixels, kernel_x, 'g');
            gyg = convolution_product(around_pixels, kernel_y, 'g');
            img->matrix[x][y].g = sqrt(gxg*gxg + gyg*gyg);
            gradients_dirs[x][y].g = normalize_gradient_direction(
                                                            atan2(gxg, gyg));

            //Blue
            gxb = convolution_product(around_pixels, kernel_x, 'b');
            gyb = convolution_product(around_pixels, kernel_y, 'b');
            img->matrix[x][y].b = sqrt(gxb*gxb + gyb*gyb);
            gradients_dirs[x][y].b = normalize_gradient_direction(
                                                            atan2(gxb, gyb));
        }
    }
    free(around_pixels);
    free_image(&original_image);
    return gradients_dirs;
}

/*
 * Removal of non-maximums: remove all "weak" values by following the angle of 
 * their gradient.
 */
void non_maximum_suppression(Image *img, Pixel **gradients_dirs)
{
    unsigned int *neighbours = malloc(6 * sizeof(unsigned int));
    Pixel pixel;

    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            pixel = img->matrix[x][y];
            get_gradient_neighbours(gradients_dirs, img->matrix, x, y, neighbours);
            if (pixel.r < neighbours[0] || pixel.r < neighbours[1])
                img->matrix[x][y].r = 0;
            if (pixel.g < neighbours[2] || pixel.g < neighbours[3])
                img->matrix[x][y].g = 0;
            if (pixel.b < neighbours[4] || pixel.b < neighbours[5])
                img->matrix[x][y].b = 0;
        }
    }
    
    //free useless variables
    for(unsigned int x = 1; x < img->width-1; x++)
        free(gradients_dirs[x]);
    free(gradients_dirs);
    free(neighbours);
}
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
    
    //flou gaussien
    //double kernel[9] = 
    //       {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
    unsigned char kernel_size = 25;
    double kernel[25] = 
        {0.0036630037, 0.0146520147, 0.0256410256, 0.0146520147, 0.0036630037,
        0.0146520147, 0.0586080586, 0.0952380952, 0.0586080586, 0.0146520147,
        0.0256410256, 0.0952380952, 0.1501831502, 0.0952380952, 0.0256410256,
        0.0146520147, 0.0586080586, 0.0952380952, 0.0586080586, 0.0146520147,
        0.0036630037, 0.0146520147, 0.0256410256, 0.0146520147, 0.0036630037};
    Pixel around_pixels[kernel_size];

    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            //Get pixels around (x,y) and the current pixel
            get_around_pixels(&original_image, x, y, 
                                    sqrt(kernel_size), (Pixel*) &around_pixels);

            //Red
            img->matrix[x][y].r = 
                convolution_product(around_pixels, (double*) &kernel, 
                                                            kernel_size, 'r');
            //Green
            img->matrix[x][y].g = 
                convolution_product(around_pixels, (double*) &kernel, 
                                                            kernel_size, 'g');
            //Blue
            img->matrix[x][y].b = 
                convolution_product(around_pixels, (double*) &kernel, 
                                                            kernel_size, 'b');
        }
    }
    free_image(&original_image);
}

/*
 * Applying the Sobel filter (edge detection).
 * Return the matrix of normalized gradient direction.
 */
unsigned int **sobel(Image *img)
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel around_pixels[9];
    unsigned int **gradients_dirs = malloc(img->width * sizeof(Pixel*));

    unsigned int newval;
    double gx, gy;
    double kernel_x[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    double kernel_y[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    
    for(unsigned int x = 0; x < img->width; x++)
    {
        gradients_dirs[x] = malloc(img->height * sizeof(Pixel));
        for(unsigned int y = 0; y < img->height; y++)
        {
            //Get 8 pixels around (x,y) and the current pixel
            get_around_pixels(&original_image, x, y, 3, (Pixel*) &around_pixels);

            //Compute only for one value because input is grayscale image
            //so r = g = b
            gx = convolution_product((Pixel*) &around_pixels,
                                                (double*) &kernel_x, 9, 'r');
            gy = convolution_product((Pixel*) &around_pixels, 
                                                (double*) &kernel_y, 9, 'r');
            newval = sqrt(gx*gx + gy*gy);
            if(newval > 255)
                newval = 255;
            img->matrix[x][y] = (Pixel) {newval, newval, newval};
            gradients_dirs[x][y] = normalize_grad_dir(atan2(gy, gx));
        }
    }
    free_image(&original_image);
    return gradients_dirs;
}

/*
 * Removal of non-maximums: remove all "weak" values by following the angle of 
 * their gradient.
 */
unsigned int **non_maximum_suppression(Image *img, unsigned int **grad_dirs)
{
    unsigned int neighbours[2];
    Pixel pixel;
    Image original_image;
    copy_image(img, &original_image);

    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            pixel = img->matrix[x][y];
            get_grad_neighbours(grad_dirs[x][y], &original_image, x, y, 
                                                (unsigned int*) &neighbours);
            if (pixel.r < neighbours[0] || pixel.r < neighbours[1])
                img->matrix[x][y] = (Pixel) {0,0,0};
        }
    }
    free_image(&original_image);
    return grad_dirs;
}

/*
 * Binarize the image to only have black or white pixels.
 * Pixels under tl are black. Pixels under th are white.
 * Pixels between tl and th depend on neighboors.
 */
void threashold(Image *img, unsigned int **grad_dirs, 
                                            unsigned int tl, unsigned int th)
{
    Pixel pixel;
    unsigned int grad_dir;
    unsigned int neighbours[2];
    //first loop to change pixels lower than tl and higher than th
    for(unsigned int x = 0; x < img->width; x++)
    {
        for(unsigned int y = 0; y < img->height; y++)
        {
            pixel = img->matrix[x][y];
            if(pixel.r > th)
                img->matrix[x][y] = (Pixel) {255, 255, 255};
            else if (pixel.r < tl)
                img->matrix[x][y] = (Pixel) {0, 0, 0};
        }
    }
    //second loop to determine pixels between tl and th
    for(unsigned int x = 1; x < img->width-1; x++)
    {
        for(unsigned int y = 1; y < img->height-1; y++)
        {
            pixel = img->matrix[x][y];
            if(pixel.r >= tl && pixel.r <= th)
            {
                grad_dir = grad_dirs[x][y] + 90;
                if (grad_dir > 135)
                    grad_dir -= 180;
                get_grad_neighbours(grad_dir, img, x, y, 
                                                (unsigned int*) &neighbours);
            
                if(neighbours[0] >= th && neighbours[1] >= th)
                    img->matrix[x][y] = (Pixel) {255, 255, 255};
                else
                    img->matrix[x][y] = (Pixel) {0, 0, 0};
            }
        }
    }
    //free useless variables
    for(unsigned int x = 0; x < img->width; x++)
        free(grad_dirs[x]);
    free(grad_dirs);
}
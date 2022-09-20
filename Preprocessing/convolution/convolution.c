#include "convolution.h"
#include "../tools/image.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Getting the 8 pixels values around the pixel at (x,y).
 * x and y are always correct depending to matrix size.
 */
void get_around_pixels(Pixel **matrix, char color, unsigned char *around_pixels,
                                    unsigned int x, unsigned int y){
    
    switch (color)
    {
        case 'r':
            around_pixels[0] = matrix[x-1][y-1].r;
            around_pixels[1] = matrix[x][y-1].r;
            around_pixels[2] = matrix[x+1][y-1].r;
            around_pixels[3] = matrix[x-1][y].r;
            around_pixels[4] = matrix[x][y].r;
            around_pixels[5] = matrix[x+1][y].r;
            around_pixels[6] = matrix[x-1][y+1].r;
            around_pixels[7] = matrix[x][y+1].r;
            around_pixels[8] = matrix[x+1][y+1].r;
            break;
        case 'g':
            around_pixels[0] = matrix[x-1][y-1].g;
            around_pixels[1] = matrix[x][y-1].g;
            around_pixels[2] = matrix[x+1][y-1].g;
            around_pixels[3] = matrix[x-1][y].g;
            around_pixels[4] = matrix[x][y].g;
            around_pixels[5] = matrix[x+1][y].g;
            around_pixels[6] = matrix[x-1][y+1].g;
            around_pixels[7] = matrix[x][y+1].g;
            around_pixels[8] = matrix[x+1][y+1].g;
            break;
        case 'b':
            around_pixels[0] = matrix[x-1][y-1].b;
            around_pixels[1] = matrix[x][y-1].b;
            around_pixels[2] = matrix[x+1][y-1].b;
            around_pixels[3] = matrix[x-1][y].b;
            around_pixels[4] = matrix[x][y].b;
            around_pixels[5] = matrix[x+1][y].b;
            around_pixels[6] = matrix[x-1][y+1].b;
            around_pixels[7] = matrix[x][y+1].b;
            around_pixels[8] = matrix[x+1][y+1].b;
            break;
        default:
    }
}

/*
 * Compute the convolution product. Not a matrix product!
 */
unsigned int convolution_product(unsigned char* pixels, float kernel[9]){
    
    unsigned int j = 8;
    float res = 0;
    for(unsigned int i = 0; i < 9; i++)
    {
        res += pixels[j] * kernel[i];
        j--;
    }
    return (unsigned int) res;    
}

/*
 * Applying a convolution in img depending of filter matrix in parameters.
 */
void convolution(Image *img, float kernel[9]){

    Image original_image;
    copy_image(img, &original_image);
    unsigned char *around_pixels = malloc(9 * sizeof(unsigned char));

    //skip edge pixels to avoid to go out of matrix
    for(unsigned int x = 1; x < img->width-1; x++){

        for(unsigned int y = 1; y < img->height-1; y++){
            //Red
            get_around_pixels(original_image.matrix, 'r', around_pixels, x, y);
            img->matrix[x][y].r = convolution_product(around_pixels, kernel);
            //Green
            get_around_pixels(original_image.matrix, 'g', around_pixels, x, y);
            img->matrix[x][y].g = convolution_product(around_pixels, kernel);
            //Blue
            get_around_pixels(original_image.matrix, 'b', around_pixels, x, y);
            img->matrix[x][y].b = convolution_product(around_pixels, kernel);
        }

    }
    free(around_pixels);
    free_image(&original_image);
}
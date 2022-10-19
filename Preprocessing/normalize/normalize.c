#include "../tools/image.h"
#include "normalize.h"

/*
 * Normalize image luminosity between 0 and 255.
 */
void normalize(Image *img){

    float tmp, max, min = 0;
    
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            tmp = img->matrix[x][y].r;
            if(tmp > max)
                max = tmp;
            if(tmp < min)
                min = tmp;            
        }
    }
    float newmin = 0;
    float newmax = 255;
    float newval = 0;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            newval = (img->matrix[x][y].r - min) * ((newmax - newmin)/(max-min)) + newmin;   
            img->matrix[x][y] = (Pixel) {newval, newval, newval};           
        }
    }
}
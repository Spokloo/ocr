#ifndef IMAGE_H
#define IMAGE_H

typedef struct Pixel
{
    unsigned int r, g, b;
} Pixel;

typedef struct Image
{
    unsigned int width;
    unsigned int height;
    struct Pixel **matrix;
    char *path;
} Image;

/*
 * Load an image into code with Image structure.
 */
Image load_image(char *path);

/*
 * Copy all content of source to destination.
 */
void copy_image(Image *src, Image *dst);

/*
 * Save the Image structure into current directory.
 */
void save_image(Image *img, char *newFileName);

/*
 * Getting the w*w pixels values around the pixel at (x,y) and put them
 * into around_pixels list.
 */
void get_around_pixels(Image *matrix, unsigned int x, unsigned int y,
                       unsigned char w, Pixel *around_pixels);

/*
 * Compute the convolution product. Not a matrix product!
 */
float convolution_product(Pixel *pixels, float *kernel, unsigned char size,
                          unsigned char color);

/*
 * Free allocated memory used by Image structure.
 */
void free_image(Image *img);

#endif
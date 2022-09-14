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

/**
 * Load an image into code with Image structure.
 */
Image load_image(char *path);

/**
 * Save the Image structure into current directory.
 */
void save_image(Image *img);

/**
 * Free allocated memory used by Image structure.
 */
void free_image(Image *img);

/**
 * Apply grayscale filter into image.
 */
void grayscale(Image *img);

#endif
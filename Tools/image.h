#ifndef IMAGE_H
#define IMAGE_H

typedef struct Pixel
{
    unsigned char r, g, b;
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
 * Return sub image of src between (x1,y1) and (x2,y2) 
 * which are position of angle in a rectangle.
 */
Image *get_sub_image(Image *src, unsigned int x1, unsigned int y1,
                                        unsigned int x2, unsigned int y2);

/*
 * Save the Image structure into current directory.
 */
void save_image(Image *img, char* newFileName);

/*
 * Free allocated memory used by Image structure.
 */
void free_image(Image *img);

#endif
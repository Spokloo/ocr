#include "image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

/*
 * Load an image into code with Image structure.
 */
Image load_image(char *path)
{
    Image img;
    img.path = path;

    SDL_Surface *tmp = IMG_Load(path);
    if (tmp == NULL)
        errx(1, "Can't load %s: %s", path, IMG_GetError());
    SDL_Surface *image_surface =
                SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0);
    if (image_surface == NULL)
        errx(1, "Can't load %s: %s", path, IMG_GetError());
    SDL_FreeSurface(tmp);

    img.width = image_surface->w;
    img.height = image_surface->h;

    //Allocate memory to save the pixels' matrix
    img.matrix = malloc(img.width * sizeof(Pixel*));
    if(img.matrix == NULL)
        errx(1, "Error during allocation of pixels' matrix.");

    Uint32 *pixels = image_surface->pixels;
    SDL_PixelFormat *format = image_surface->format;
    Uint8 r, g, b;
    SDL_LockSurface(image_surface);
    for (unsigned int x = 0; x < img.width; x++)
    {
        img.matrix[x] = malloc(img.height * sizeof(Pixel));
        if(img.matrix[x] == NULL)
            errx(1, "Error during allocation of pixels' matrix.");

        //Fill the pixels' matrix with Pixel structure (RGB value)
        for (unsigned int y = 0; y < img.height; y++)
        {
            SDL_GetRGB(pixels[y * img.width + x], format, &r, &g, &b);
            img.matrix[x][y] = (Pixel) {r, g, b};
        }
    }
    SDL_UnlockSurface(image_surface);
    SDL_FreeSurface(image_surface);
    SDL_Quit();

    return img;
}

/*
 * Copy all content of source to destination.
 */
void copy_image(Image *src, Image *dst)
{
    dst->path = src->path;
    dst->height = src->height;
    dst->width = src->width;

    //Allocate memory
    dst->matrix = malloc(src->width * sizeof(Pixel*));
    if(dst->matrix == NULL)
        errx(1, "Error during allocation of pixels' matrix.");

    for (unsigned int x = 0; x < src->width; x++)
    {
        dst->matrix[x] = malloc(src->height * sizeof(Pixel));
        if(dst->matrix[x] == NULL)
            errx(1, "Error during allocation of pixels' matrix.");

        //Copy each pixel
        for (unsigned int y = 0; y < src->height; y++)
            dst->matrix[x][y] = src->matrix[x][y];
    }

}

/*
 * Return sub image of src between (x1,y1) and (x2,y2) 
 * which are position of angle in a rectangle.
 */
Image *get_sub_image(Image *src, unsigned int x1, unsigned int y1,
                                        unsigned int x2, unsigned int y2)
{
    if(x1 > src->width || x2 > src->width || 
                                        y1 > src->height || y2 > src->height)
        errx(1, "Error when getting sub image. Invalid coordinates.");
    Image *dst = malloc(sizeof(Image));
    dst->path = "";
    dst->height = y2 - y1;
    dst->width = x2 - x1;
    unsigned int ytmp;
    dst->matrix = malloc(dst->width * sizeof(Pixel*));
    if(dst->matrix == NULL)
        errx(1, "Error during allocation of pixels' matrix.");
    for (unsigned int x = 0; x < dst->width; x++)
    {
        ytmp = y1;
        dst->matrix[x] = malloc(dst->height * sizeof(Pixel));
        if(dst->matrix[x] == NULL)
            errx(1, "Error during allocation of pixels' matrix.");

        //Fill the pixels' matrix with Pixel structure (RGB value)
        for (unsigned int y = 0; y < dst->height; y++)
        {
            dst->matrix[x][y] = src->matrix[x1][ytmp];
            ytmp++;
        }
        x1++;
    }
    return dst;
}

/*
 * Save the Image structure into current directory.
 */
void save_image(Image *img, char* newFileName)
{
    SDL_Surface *image_surface =
            SDL_CreateRGBSurfaceWithFormat(0, img->width, img->height, 32,
                                                    SDL_PIXELFORMAT_RGB888);

    Uint32 *pixels = image_surface->pixels;
    SDL_PixelFormat *format = image_surface->format;
    Pixel myPixel;
    SDL_LockSurface(image_surface);

    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            myPixel = img->matrix[x][y];
            pixels[y * image_surface->w + x] = SDL_MapRGB(format, myPixel.r,
                                                        myPixel.g, myPixel.b);
        }
    }

    SDL_UnlockSurface(image_surface);
    SDL_SaveBMP(image_surface , newFileName);
    SDL_FreeSurface(image_surface);
    SDL_Quit();
}

/*
 * Free allocated memory used by Image structure.
 */
void free_image(Image *img)
{
    unsigned width = img->width;
    for(unsigned int i = 0; i < width; i++)
        free(img->matrix[i]);
    free(img->matrix);
}
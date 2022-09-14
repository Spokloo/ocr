#include "image.h"
#include "sdl_tools.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

/*
 * Load an image into code with Image structure.
 */
Image load_image(char *path){

    Image img;
    img.path = path;

    SDL_Surface *image_surface;
    image_surface = IMG_Load(path);
    if (!image_surface)
        errx(1, "Can't load %s: %s", path, IMG_GetError());

    img.width = image_surface->w;
    img.height = image_surface->h;

    //Allocate memory to save the pixels' matrix
    img.matrix = malloc(img.width * sizeof(Pixel*));
    if(img.matrix == NULL)
        errx(1, "Error during allocation of pixels' matrix.");

    for (unsigned int i = 0; i < img.width; i++)
    {
        img.matrix[i] = malloc(img.height * sizeof(Pixel));
        if(img.matrix[i] == NULL)
            errx(1, "Error during allocation of pixels' matrix.");
    }

    //Fill the pixels' matrix with Pixel structure (RGB value)
    Uint32 pixel;
    Uint8 r, g, b;
    for (unsigned int x = 0; x < img.width; x++)
    {
        for (unsigned int y = 0; y < img.height; y++)
        {
            pixel = get_pixel(image_surface, x, y);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            img.matrix[x][y].r = r;
            img.matrix[x][y].g = g;
            img.matrix[x][y].b = b;
        }
    }
    return img;
}

/*
 * Save the Image structure into current directory.
 */
void save_image(Image *img){

    SDL_Surface *image_surface =
            SDL_CreateRGBSurface(0, img->width, img->height, 32, 0, 0, 0, 0);

    Uint32 SDL_pixel;
    Pixel pixel;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            pixel = img->matrix[x][y];
            SDL_pixel = SDL_MapRGB(image_surface->format, pixel.r, pixel.g, pixel.b);
            put_pixel(image_surface, x, y, SDL_pixel);
        }
    }

    SDL_SaveBMP(image_surface , "result_grayscale.png");
    SDL_FreeSurface(image_surface);
}

/*
 * Free allocated memory used by Image structure.
 */
void free_image(Image *img){

    unsigned width = img->width;
    for(unsigned int i = 0; i < width; i++)
        free(img->matrix[i]);
    free(img->matrix);
}

/*
 * Apply grayscale filter into image.
 */
void grayscale(Image *img){

    Pixel pixel;
    unsigned int average;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            pixel = img->matrix[x][y];
            average = 0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b;

            img->matrix[x][y].r = average;
            img->matrix[x][y].g = average;
            img->matrix[x][y].b = average;
        }
    }
}
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

    SDL_Surface *image_surface = NULL;
    image_surface = IMG_Load(path);
    if (!image_surface)
        errx(1, "Can't load %s: %s", path, IMG_GetError());

    img.width = image_surface->w;
    img.height = image_surface->h;

    //Allocate memory to save the pixels' matrix
    img.matrix = malloc(img.width * sizeof(Pixel*));
    if(img.matrix == NULL)
        errx(1, "Error during allocation of pixels' matrix.");

    Uint32 pixel;
    Uint8 r, g, b;
    for (unsigned int x = 0; x < img.width; x++)
    {
        img.matrix[x] = malloc(img.height * sizeof(Pixel));
        if(img.matrix[x] == NULL)
            errx(1, "Error during allocation of pixels' matrix.");

        //Fill the pixels' matrix with Pixel structure (RGB value)
        for (unsigned int y = 0; y < img.height; y++)
        {
            pixel = get_pixel(image_surface, x, y);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            img.matrix[x][y] = (Pixel) {r, g, b};
        }
    }

    SDL_FreeSurface(image_surface);
    SDL_Quit();
    return img;
}

/*
 * Copy all content of source to destination.
 */
void copy_image(Image *src, Image *dst){

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
 * Save the Image structure into current directory.
 */
void save_image(Image *img, char* newFileName){

    SDL_Surface *image_surface =
            SDL_CreateRGBSurface(0, img->width, img->height, 32, 0, 0, 0, 0);

    Uint32 SDL_pixel;
    Pixel pixel;
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            pixel = img->matrix[x][y];
            SDL_pixel = SDL_MapRGB(image_surface->format, 
                                                    pixel.r, pixel.g, pixel.b);
            put_pixel(image_surface, x, y, SDL_pixel);
        }
    }

    SDL_SaveBMP(image_surface , newFileName);
    SDL_FreeSurface(image_surface);
    SDL_Quit();
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
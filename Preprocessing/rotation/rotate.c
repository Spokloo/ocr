#include "../tools/image.h"
#include "rotate.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * Rotate clockwise the image with the given angle in degrees thanks to SDL functions.
 */
void rotateSDL(char *img_path, int angle){

    SDL_Surface *surface = IMG_Load(img_path);
    SDL_Window *win = SDL_CreateWindow("Rotation of image", 0, 0, surface->w, surface->h, SDL_WINDOW_HIDDEN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surface);
    SDL_RenderCopyEx(ren, tex, NULL, NULL, angle, NULL, SDL_FLIP_HORIZONTAL);

    surface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(ren, NULL, surface->format->format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, "result_rotation.jpg");
    
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_FreeSurface(surface);
    SDL_Quit();
}

/*
 * Rotate clockwise the image with the given angle in degrees.
 */
void rotate(Image *img, short angle_deg){

    Image original_image;
    copy_image(img, &original_image);

    //convert degrees into radian
    float angle_rad = - (angle_deg * (M_PI / 180));
    long new_x, new_y, xdiff, ydiff;
    //get center' coordinates of the image
    long x0 = img->width / 2;
    long y0 = img->height / 2;
    float cos_angle = cos(angle_rad);
    float sin_angle = sin(angle_rad);

    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            //apply the rotation matrix to each pixels related to the center of the image
            xdiff = x - x0;
            ydiff = y - y0;
            new_x = xdiff * cos_angle - ydiff * sin_angle + x0;
            new_y = xdiff * sin_angle + ydiff * cos_angle + y0;

            //if the new position of pixel isn't in image size, fill with black pixel
            if (new_x >= 0 && new_x < img->width && new_y >= 0 && new_y < img->height)
                img->matrix[x][y] = original_image.matrix[new_x][new_y];
            else
                img->matrix[x][y] = (Pixel) {0, 0, 0};
        }
    }
    free_image(&original_image);
}
#ifndef SDL_TOOLS_H
#define SDL_TOOLS_H

#include <SDL2/SDL.h>

/**
 * Get the pixel value at (x,y) on the SDL Surface.
 */
Uint32 get_pixel(SDL_Surface *surface, int x, int y);

/**
 * Set the pixel at (x, y) to the given value on the SDL Surface.
 */
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif

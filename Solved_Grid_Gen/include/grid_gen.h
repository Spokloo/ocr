#ifndef GRID_GEN_H
#define GRID_GEN_H

#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "solver_fun.h"

void place_image(Image *dest, int digit, int x, int y);
void printHelp();
void construct_grid(char *old_path, char *solved_path);

#endif

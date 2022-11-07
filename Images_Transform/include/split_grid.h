#ifndef SPLIT_GRID_H
#define SPLIT_GRID_H

#include "../../Tools/image.h"

/*
 * Split image in 81 to get each cells of Sudoku.
 * Fill the list 'cells' of all cells images.
 */
void get_cells(Image *img, Image **cells);

#endif
#ifndef SPLIT_GRID_H
#define SPLIT_GRID_H

#include "image.h"

/*
 * Split image in 81 to get each cells of Sudoku.
 * Fill the list 'cells' of all cells images.
 */
void get_cells(Image *img, Image **cells);

/*
 * Resize the image to fit the number or create a white 28*28 image if there is
 * no number.
 */
Image *get_number_in_cell(Image *cell);

/*
 * Resize the image to 28*28 pixels. 
 */
Image *resize_28(Image *img);

#endif
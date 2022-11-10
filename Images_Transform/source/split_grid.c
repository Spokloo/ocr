#include "../include/split_grid.h"
#include "../../Tools/image.h"

/*
 * Split image in 81 to get each cells of Sudoku.
 * Fill the list 'cells' of all cells images.
 */
void get_cells(Image *img, Image **cells)
{
    unsigned char step = img->height / 9;
    unsigned char index = 0;
    for (unsigned int x = 0; x < img->width - step; x += step)
    {
        for (unsigned int y = 0; y < img->height - step; y += step)
        {
            cells[index] = get_sub_image(img, x, y, x + step, y + step);
            index++;
        }
    }
}
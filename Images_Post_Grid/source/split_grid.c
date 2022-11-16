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

/*
 * Resize the image to fit the number or create a white 28*28 image if there is
 * no number.
 */
Image *get_number_in_cell(Image *cell)
{
    unsigned int size = cell->width;
    unsigned int center = size / 2;
    unsigned int x_min = size, x_max = 0, y_min = size, y_max = 0;
    char y_min_change = 1, y_max_change = 1, x_min_change = 1, x_max_change = 1;
    char blank = 1;

    // start searching near the center
    char step = size / 8;
    unsigned int x_min_prev = center - step, x_max_prev = center + step,
                 y_min_prev = center - step, y_max_prev = center + step;

    // while the coordinates change, we continue to search
    // else we have numbers coordinates
    while (y_min_change || y_max_change || x_min_change || x_max_change)
    {
        blank++;
        if (y_min_change)
            y_min_prev--;

        if (y_max_change)
            y_max_prev++;

        if (x_min_change)
            x_min_prev--;

        if (x_max_change)
            x_max_prev++;

        y_min_change = 0;
        y_max_change = 0;
        x_min_change = 0;
        x_max_change = 0;

        // avoid segfault
        if (x_min_prev < 0)
            x_min_prev = 0;
        if (x_max_prev >= size)
            x_max_prev = size - 1;
        if (y_min_prev < 0)
            y_min_prev = 0;
        if (y_max_prev >= size)
            y_max_prev = size - 1;

        for (unsigned int x = x_min_prev; x <= x_max_prev; x++)
        {
            for (unsigned int y = y_min_prev; y <= y_max_prev; y++)
            {
                if (cell->matrix[x][y].g == 255)
                {
                    if (y < y_min)
                    {
                        y_min = y;
                        y_min_change = 1;
                    }
                    if (y > y_max)
                    {
                        y_max = y;
                        y_max_change = 1;
                    }
                    if (x < x_min)
                    {
                        x_min = x;
                        x_min_change = 1;
                    }
                    if (x > x_max)
                    {
                        x_max = x;
                        x_max_change = 1;
                    }
                }
            }
        }
    }
    // if we detect a number, cut image
    if (blank != 2)
    {
        Image *nb = get_sub_image(cell, x_min, y_min, x_max, y_max);
        free_image(cell);
        return nb;
    }
    // else return a blank image of 28*28
    else
    {
        Image *nb = get_sub_image(cell, 0, 0, 28, 28);
        free_image(cell);
        Pixel white = {255, 255, 255};
        for (unsigned int x = 0; x < nb->width; x++)
        {
            for (unsigned int y = 0; y < nb->height; y++)
                nb->matrix[x][y] = white;
        }
        return nb;
    }
}
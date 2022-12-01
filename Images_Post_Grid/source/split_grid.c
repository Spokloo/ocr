#include "../include/split_grid.h"
#include "../../Tools/image.h"
#include <stdlib.h>
#include <err.h>

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
            cells[index] = get_sub_image(img, y, x, y + step, x + step);
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
    int size = cell->width;
    unsigned int center = size / 2;
    int x_min = size, x_max = 0, y_min = size, y_max = 0;
    char y_min_change = 1, y_max_change = 1, x_min_change = 1, x_max_change = 1;
    char blank = 1;

    // start searching near the center
    unsigned int step = size / 8;
    int x_min_prev = center - step, x_max_prev = center + step,
                 y_min_prev = center - step, y_max_prev = center + step;

    // while we discover new black pixel, continue to search
    // else we have numbers rectangle
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

        for (int x = x_min_prev; x <= x_max_prev; x++)
        {
            for (int y = y_min_prev; y <= y_max_prev; y++)
            {
                if (cell->matrix[x][y].r == 0)
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
    unsigned int x_len = x_max - x_min;
    unsigned int y_len = y_max - y_min;
    step /= 2;
    if (blank != 2 && x_len > step && y_len > step && x_len < cell->width - step && y_len < cell->height - step)
    {
        // to have a perfect square
        if(x_len % 2 == 1)
            x_max++;
        if(y_len % 2 == 1)
            y_max++;

        // get coordinates of a square and not only the number 
        // to avoid distortion when resize
        if(y_len > x_len)
        {
            y_len -= x_len;
            y_len /= 2;
            x_min -= y_len;
            x_max += y_len;
            if (x_min < 0)
                x_min = 0;
            if (x_max >= size)
                x_max = size - 1;
        }
        else
        {
            x_len -= y_len;
            x_len /= 2;
            y_min -= x_len;
            y_max += x_len;
            if (y_min < 0)
                y_min = 0;
            if (y_max >= size)
                y_max = size - 1;
        }
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

/*
 * Resize the image to 28*28 pixels. 
 */
Image *resize_28(Image *img)
{
    // if it's already a white square created when getting number in cell
    // do nothing
    if(img->height == 28 && img->width == 28)
        return img;
    Image *dst = malloc(sizeof(Image));
    dst->path = "";
    dst->height = 28;
    dst->width = 28;
    dst->matrix = malloc(dst->width * sizeof(Pixel *));
    if (dst->matrix == NULL)
            errx(1, "Error during allocation of pixels' matrix.");

    float scale_x = 28.0 / img->width;
    float scale_y = 28.0 / img->height;
    for (unsigned int x = 0; x < dst->width; x++)
    {
        dst->matrix[x] = malloc(dst->height * sizeof(Pixel));
        if (dst->matrix[x] == NULL)
            errx(1, "Error during allocation of pixels' matrix.");

        for (unsigned int y = 0; y < dst->height; y++)
            dst->matrix[x][y] = img->matrix[(int) (x / scale_x)][(int) (y / scale_y)];
    }

    free_image(img);
    free(img);
    return dst;
}

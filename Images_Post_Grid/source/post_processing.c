#include "../include/post_processing.h"
#include "../../Tools/image.h"

/*
 * Compute a threashold with Otsü algorithm.
 */
unsigned int compute_high_threashold(Image *img)
{
    // https://www.ipol.im/pub/art/2016/158/article_lr.pdf
    // build image histogram
    unsigned long histo[256];
    for (unsigned int i = 0; i < 256; i++)
        histo[i] = 0;
    // skip borders because there are not treated by Sobel
    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
            histo[img->matrix[x][y].r] += 1;
    }
    // Apply Otsu algorithm
    float total_sum = 0, partial_sum = 0, w0 = 0, w1 = 0, u0 = 0, u1 = 0,
          sigma2 = 0, s2_max = 0, tmp = 0;
    unsigned int t = 0;
    unsigned long size = img->height * img->width;
    for (unsigned int i = 0; i < 256; i++)
        total_sum += i * histo[i];

    for (unsigned int i = 0; i < 256; i++)
    {
        w0 += histo[i];
        if (w0 == 0)
            continue;
        w1 = size - w0;
        partial_sum += i * histo[i];
        u0 = partial_sum / w0;
        u1 = (total_sum - partial_sum) / w1;
        tmp = u0 - u1;
        sigma2 = w0 * w1 * tmp * tmp;
        if (sigma2 > s2_max)
        {
            t = i;
            s2_max = sigma2;
        }
    }
    return t;
}

/*
 * Apply a binarization on a cell.
 */
void post_processing(Image *cell)
{
    unsigned int t = compute_high_threashold(cell);
    Pixel white = {255, 255, 255};
    Pixel black = {0, 0, 0};
    for (unsigned int x = 0; x < cell->width; x++)
    {
        for (unsigned int y = 0; y < cell->height; y++)
        {
            if (cell->matrix[x][y].r >= t)
                cell->matrix[x][y] = black;
            else
                cell->matrix[x][y] = white;
        }
    }
}
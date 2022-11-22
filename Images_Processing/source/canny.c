#include "../include/canny.h"
#include "../../Tools/image.h"
#include "../../Tools/image_tools.h"
#include "../include/canny_tools.h"
#include <math.h>
#include <stdlib.h>

/*
 * Applying the Sobel filter (edge detection).
 * Return the matrix of normalized gradient direction.
 */
unsigned int **sobel(Image *img)
{
    Image original_image;
    copy_image(img, &original_image);
    Pixel around_pixels[9];
    unsigned int **gradients_dirs = malloc(img->width * sizeof(unsigned int *));

    unsigned int newval;
    double gx, gy;
    float kernel_x[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    float kernel_y[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    for (unsigned int x = 1; x < img->width - 1; x++)
    {
        gradients_dirs[x] = malloc(img->height * sizeof(unsigned int));
        for (unsigned int y = 1; y < img->height - 1; y++)
        {
            // Get 8 pixels around (x,y) and the current pixel
            get_around_pixels(&original_image, x, y, 3,
                              (Pixel *)&around_pixels);

            // Compute only for one value because input is grayscale image
            // so r = g = b
            gx = convolution_product((Pixel *)&around_pixels,
                                     (float *)&kernel_x, 9);
            gy = convolution_product((Pixel *)&around_pixels,
                                     (float *)&kernel_y, 9);
            newval = sqrt(gx * gx + gy * gy);
            if (newval > 255)
                newval = 255;
            img->matrix[x][y] = (Pixel){newval, newval, newval};
            gradients_dirs[x][y] = normalize_grad_dir(atan2(gy, gx));
        }
    }
    free_image(&original_image);
    return gradients_dirs;
}

/*
 * Removal of non-maximums: remove all "weak" values by following the angle of
 * their gradient.
 */
unsigned int **non_maximum_suppression(Image *img, unsigned int **grad_dirs)
{
    unsigned int neighbours[2];
    Pixel pixel;
    Image original_image;
    copy_image(img, &original_image);

    // skip edge pixels to avoid to go out of matrix
    for (unsigned int x = 1; x < img->width - 1; x++)
    {
        for (unsigned int y = 1; y < img->height - 1; y++)
        {
            pixel = img->matrix[x][y];
            get_grad_neighbours(grad_dirs[x][y], &original_image, x, y,
                                (unsigned int *)&neighbours);
            if (pixel.r < neighbours[0] || pixel.r < neighbours[1])
                img->matrix[x][y] = (Pixel){0, 0, 0};
        }
    }
    free_image(&original_image);
    return grad_dirs;
}

/*
 * Binarize the image to only have black or white pixels.
 * Pixels under tl are black. Pixels under th are white.
 * Pixels between tl and th depend on neighboors.
 */
void threashold(Image *img, unsigned int **grad_dirs, unsigned int tl,
                unsigned int th)
{
    Pixel pixel;
    unsigned int grad_dir;
    unsigned int neighbours[2];
    Pixel black = {0, 0, 0};
    Pixel white = {255, 255, 255};
    // first loop to change pixels lower than tl and higher than th
    for (unsigned int x = 1; x < img->width - 1; x++)
    {
        for (unsigned int y = 1; y < img->height - 1; y++)
        {
            pixel = img->matrix[x][y];
            if (pixel.r > th)
                img->matrix[x][y] = white;
            else if (pixel.r < tl)
                img->matrix[x][y] = black;
        }
    }
    // second loop to determine pixels between tl and th
    for (unsigned int x = 1; x < img->width - 1; x++)
    {
        for (unsigned int y = 1; y < img->height - 1; y++)
        {
            pixel = img->matrix[x][y];
            if (pixel.r >= tl && pixel.r <= th)
            {
                grad_dir = grad_dirs[x][y] + 90;
                if (grad_dir > 135)
                    grad_dir -= 180;
                get_grad_neighbours(grad_dir, img, x, y,
                                    (unsigned int *)&neighbours);

                if (neighbours[0] >= th && neighbours[1] >= th)
                    img->matrix[x][y] = white;
                else
                    img->matrix[x][y] = black;
            }
        }
    }
    // black pixels in borders
    for (unsigned int x = 0; x < img->width; x++)
    {
        img->matrix[x][0] = black;
        img->matrix[x][img->height - 1] = black;
    }
    for (unsigned int y = 0; y < img->height; y++)
    {
        img->matrix[0][y] = black;
        img->matrix[img->width - 1][y] = black;
    }
}

/*
 * Compute high threashold thanks to Otsu Algorithm.
 */
unsigned int compute_high_threashold(Image *img)
{
    // https://www.ipol.im/pub/art/2016/158/article_lr.pdf
    // build image histogram
    unsigned long histo[256];
    for (unsigned int i = 0; i < 256; i++)
        histo[i] = 0;
    // skip borders because there are not treated by Sobel
    for (unsigned int x = 1; x < img->width - 1; x++)
    {
        for (unsigned int y = 1; y < img->height - 1; y++)
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
 * Apply the Canny filter.
 * (Sobel, Non-Maximum Suppression and Double Threashold)
 */
void canny(Image *img)
{
    unsigned int **gradients_dirs = sobel(img);
    // non_maximum_suppression(img, gradients_dirs);
    unsigned int th = compute_high_threashold(img);
    unsigned int tl = 0.5 * th;
    threashold(img, gradients_dirs, tl, th);
    for (unsigned int x = 1; x < img->width - 1; x++)
        free(gradients_dirs[x]);
    free(gradients_dirs);
}

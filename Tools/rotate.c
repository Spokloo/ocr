#include "rotate.h"
#include "image.h"
#include <math.h>
/*
 * Rotate clockwise the image with the given angle in degrees.
 */
void rotate(Image *img, short angle_deg)
{

    Image original_image;
    copy_image(img, &original_image);

    // convert degrees into radian
    float angle_rad = -(angle_deg * (M_PI / 180));
    long new_x, new_y, xdiff, ydiff;
    // get center' coordinates of the image
    long x0 = img->width / 2;
    long y0 = img->height / 2;
    float cos_angle = cos(angle_rad);
    float sin_angle = sin(angle_rad);

    for (unsigned int x = 0; x < img->width; x++)
    {
        for (unsigned int y = 0; y < img->height; y++)
        {
            // apply the rotation matrix to each pixels related to the center
            xdiff = x - x0;
            ydiff = y - y0;
            new_x = xdiff * cos_angle - ydiff * sin_angle + x0;
            new_y = xdiff * sin_angle + ydiff * cos_angle + y0;

            // if the new position of pixel isn't in image size,
            // fill with black pixel
            if (new_x >= 0 && new_x < img->width && new_y >= 0 &&
                new_y < img->height)
                img->matrix[x][y] = original_image.matrix[new_x][new_y];
            else
                img->matrix[x][y] = (Pixel){0, 0, 0};
        }
    }
    free_image(&original_image);
}

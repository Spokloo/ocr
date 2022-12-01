#include "../include/perspective.h"
#include "../../Tools/image.h"
#include "../../Images_Post_Grid/include/perspective_correction.h"
#include "../../Images_Post_Grid/include/split_grid.h"
#include <stdlib.h>

void extract_cells(Image *img)
{
    Image **cells = malloc(81 * sizeof(Image *));
    get_cells(img, cells);
    char name[8] = "0i.jpeg";
    for (unsigned char i = 0; i < 81; i++)
    {
        if (i < 10)
            name[1] = i + '0';
        else
        {
            name[0] = i / 10 + '0';
            name[1] = i % 10 + '0';
        }
        save_image(cells[i], name);
        free_image(cells[i]);
        free(cells[i]);
    }
    free(cells);
}

void perspective(Image *img, Square **gs, Image ***result_imgs)
{
    // Perspective correction
    int points[8] = { (*gs)->p1.x, (*gs)->p1.y, (*gs)->p2.x, (*gs)->p2.y,
        (*gs)->p3.x, (*gs)->p3.y, (*gs)->p4.x, (*gs)->p4.y };

    correct_perspective(img, points);

    // Storing image
    (*result_imgs)[4] = img;
    save_image(img, "corrected_perspective.jpeg");

    // Extracting the 81 cells
    // extract_cells(img);
}


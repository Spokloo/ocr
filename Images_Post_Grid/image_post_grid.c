#include "image_post_grid.h"
#include "../Tools/image.h"
#include "include/perspective_correction.h"
#include "include/split_grid.h"
#include "include/post_processing.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(1, "Give an image path or 'all' as arguments");

    Image img = load_image(argv[1]);

    //- - - - Correct perspective - - - - - -
    int src1[8] = {0, 0, 1000, 0, 1000, 1000, 0, 1000};
    int src2[8] = {343, 216, 1149, 212, 1159, 1027, 348, 1026};
    int src3[8] = {130, 89, 650, 89, 650, 609, 130, 609};
    int src4[8] = {416, 162, 1545, 180, 1540, 1306, 423, 1308};
    int src5[8] = {630, 180, 1365, 695, 849, 1435, 110, 915};
    int src6[8] = {70, 65, 1940, 65, 2080, 1830, 40, 1900};
    correct_perspective(&img, src1);

    // - - - Extract each cells - - - - -
    Image **cells = malloc(81 * sizeof(Image *));
    get_cells(&img, cells);
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
        post_processing(cells[i]);
        cells[i] = get_number_in_cell(cells[i]);
        save_image(cells[i], name);
        free_image(cells[i]);
        free(cells[i]);
    }
    free(cells);
    save_image(&img, "result.jpeg");
    free_image(&img);
    return 0;
}

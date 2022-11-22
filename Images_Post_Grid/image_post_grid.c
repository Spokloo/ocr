#include "image_post_grid.h"
#include "../Tools/image.h"
#include "include/perspective_correction.h"
#include "include/post_processing.h"
#include "include/split_grid.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_filters(char *path, char *newName)
{
    int src1[8] = {0, 0, 1000, 0, 1000, 1000, 0, 1000};
    int src2[8] = {343, 216, 1149, 212, 1159, 1027, 348, 1026};
    int src3[8] = {130, 89, 650, 89, 650, 609, 130, 609};
    int src4[8] = {416, 162, 1545, 180, 1540, 1306, 423, 1308};
    int src5[8] = {630, 180, 1365, 695, 849, 1435, 110, 915};
    int src6[8] = {70, 65, 1940, 65, 2080, 1830, 40, 1900};
    int *src[8] = {src1, src2, src3, src4, src5, src6};
    size_t i = 0;
    for(; path[i] != '\0'; i++)
    {
        if(path[i] >= '1' && path[i] <= '9')
            break;
    }
    if(path[i] == '\0' || path[i+1] == '\0')
        errx(1, "Wrong file format");
    i = strtol(path + i, NULL, 10);
    char subName[17] = "image_00_00.jpeg";
    subName[7] = i + '0';
    subName[16] = '\0';
    Image **cells = malloc(81 * sizeof(Image *));
    Image *tmp;

    Image img = load_image(path);

    // - - - Correct perspective - - - - -
    correct_perspective(&img, src[i - 1]);

    // - - - Extract each cells - - - - -

    get_cells(&img, cells);
    for (unsigned char i = 0; i < 81; i++)
    {
        if (i < 10)
        {
            subName[9] = '0';
            subName[10] = i + '0';
        }
        else
        {
            subName[9] = i / 10 + '0';
            subName[10] = i % 10 + '0';
        }
        post_processing(cells[i]);
        tmp = get_number_in_cell(cells[i]);
        free(cells[i]);
        cells[i] = tmp;
        cells[i] = resize_28(cells[i]);
        save_image(cells[i], subName);
        free_image(cells[i]);
        free(cells[i]);
    }
    save_image(&img, newName);
    free_image(&img);
    free(cells);
}

void testall()
{
    // char path[29] = "../Images_Test/image_00.jpeg";
    // path[28] = '\0';
    char path[42] = "../Images_Processing/result_image_00.jpeg";
    path[41] = '\0';
    char newName[21] = "result_image_00.jpeg";
    newName[20] = '\0';

    for (size_t i = 1; i <= 6; i++)
    {
        // path[22] = i + '0';
        path[35] = i + '0';
        newName[14] = i + '0';
        printf("Work on %s\n", path);

        apply_filters(path, newName);

        printf("==============================\n");
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(1, "Give an image path or 'all' as arguments");
    if (strcmp(argv[1], "all") == 0)
        testall();
    else
        apply_filters(argv[1], "result.jpeg");
    return 0;
}

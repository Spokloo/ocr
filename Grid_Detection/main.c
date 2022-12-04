#include "../Tools/image.h"
#include "include/houghtransform.h"
#include "include/auto_rotation.h"
#include "include/squares.h"
#include "include/perspective.h"
#include <err.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(1, "Usage: ./main <path to image>");

    Image img = load_image(argv[1]);
    Image copy_img;
    copy_image(&img, &copy_img);

    int **real_lines = NULL;
    unsigned int lines_len = 0;
    Square *sq = NULL;
    Square *gs = NULL;

    Image **result_imgs = malloc(sizeof(Image*) * 5);
    for (int i = 0; i < 5; i++)
        result_imgs[i] = NULL;

    time_t start = time(NULL);
    hough_transform(&img, &lines_len, &real_lines);
    result_imgs[0] = &img;
    save_image(&img, "results/step_01a_hough_lines.jpeg");

    auto_rotation(&img, &copy_img, &lines_len, &real_lines, &result_imgs);
    save_image(&img, "results/step_01b_auto_rotation.jpeg");
    squares(&img, &lines_len, &real_lines, &sq, &gs, &result_imgs);
    save_image(result_imgs[2], "results/step_02_squares_detection.jpeg");
    save_image(result_imgs[3], "results/step_03_main_grid_detection.jpeg");
    perspective(&img, &gs, &result_imgs);
    time_t end = time(NULL);

    printf("Execution took %lds.\n", (unsigned long) difftime(end, start));

    for (unsigned int i = 0; i < lines_len; i++)
        free(real_lines[i]);
    free(real_lines);

    free(sq);
    free_image(result_imgs[2]);
    free(result_imgs[2]);
    free(result_imgs);
    free_image(&img);
}

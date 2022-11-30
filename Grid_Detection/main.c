#include "../Tools/image.h"
#include "houghtransform.h"
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
    Square *gs = NULL;

    time_t start = time(NULL);
    hough_transform(&img, &lines_len, &real_lines);
    save_image(&img, "hough_lines.jpeg");

    auto_rotation(&img, &copy_img, &lines_len, &real_lines);
    squares(&img, &lines_len, &real_lines, &gs);
    perspective(&img, &gs);
    time_t end = time(NULL);

    printf("Execution took %lds.\n", (unsigned long) difftime(end, start));

    save_image(&img, "result_hough.jpeg");
    free_image(&img);
}

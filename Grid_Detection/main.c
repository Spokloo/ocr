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

    time_t start = time(NULL);
    hough_transform(&img);
    time_t end = time(NULL);

    printf("Execution took %lds.\n", (unsigned long) difftime(end, start));

    save_image(&img, "result_hough.jpeg");
    free_image(&img);
}

#include "../Tools/image.h"
#include "houghtransform.h"
#include <err.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3)
        errx(1, "Usage: ./main <path to image> <threshold>");

    Image img = load_image(argv[1]);
    double threshold = atof(argv[2]);
    hough_transform(&img, threshold);
    save_image(&img, "result_hough.jpeg");
    free_image(&img);
}

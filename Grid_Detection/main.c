#include <err.h>
#include "houghtransform.h"
#include "../Tools/image.h"

int main(int argc, char** argv) {
    if (argc != 2)
        errx(1, "A path to an image is necessary");

    Image img = load_image(argv[1]);
    hough_transform(&img);
    save_image(&img, "result_hough.jpg");
    free_image(&img);
}

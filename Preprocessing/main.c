#include "contrast/contrast.h"
#include "grayscale/grayscale.h"
#include "canny/canny.h"
#include "tools/image.h"
#include <err.h>

int main(int argc, char **argv)
{
    if(argc != 2)
        errx(1, "Give an image path");
    
    Image img = load_image(argv[1]);

    grayscale(&img);
    //contrast(&img, 128);
    blur(&img);
    sobel(&img);
    save_image(&img, "result.jpg");
    free_image(&img);

    return 0;
}
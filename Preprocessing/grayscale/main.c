#include <err.h>
#include "../tools/image.h"
#include "grayscale.h"

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path as argument");
    Image img = load_image(argv[1]);
    grayscale(&img);
    save_image(&img, "result_grayscale.jpg");
    free_image(&img);
    return 0;
}
#include <err.h>
#include "../tools/image.h"
#include "grayscale.h"

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path as argument");
    Image wow = load_image(argv[1]);
    grayscale(&wow);
    save_image(&wow, "result_grayscale.jpg");
    free_image(&wow);
    return 0;
}
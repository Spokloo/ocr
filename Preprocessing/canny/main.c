#include "../tools/image.h"
#include "canny.h"
#include "../grayscale/grayscale.h"
#include <err.h>

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path");
    Image wow = load_image(argv[1]);
    grayscale(&wow);
    canny(&wow);
    save_image(&wow, "result_canny.jpg");
    free_image(&wow);

    return 0;
}
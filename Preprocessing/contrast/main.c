#include "../tools/image.h"
#include "contrast.h"
#include <stdlib.h>
#include <err.h>

int main(int argc, char **argv){

    if(argc != 3)
        errx(1, "Give an image path and a contrast factor as arguments");
    int param = strtol(argv[2], NULL, 10);
    Image wow = load_image(argv[1]);
    contrast(&wow, param);
    save_image(&wow, "result_contrast.jpg");
    free_image(&wow);

    return 0;
}
#include <err.h>
#include "rotate.h"
#include <stdlib.h>
#include <stdio.h>
#include "../tools/image.h"

int main(int argc, char **argv){

    if(argc != 3)
        errx(1, "Give an image path and an angle as arguments");
    int param = strtoul(argv[2], NULL, 10);
    //rotateSDL(argv[1], param);

    Image wow = load_image(argv[1]);
    rotate(&wow, param);
    save_image(&wow, "result_rotation.jpg");
    free_image(&wow);
    
    return 0;
}

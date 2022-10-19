#include "../tools/image.h"
#include "normalize.h"
#include <stdlib.h>
#include <err.h>

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path as argument");
    
    Image wow = load_image(argv[1]);
    normalize(&wow);
    save_image(&wow, "result_normalize.jpg");
    free_image(&wow);

    return 0;
}
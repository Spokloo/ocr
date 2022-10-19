#include "../tools/image.h"
#include "morphological_ops.h"
#include "../grayscale/grayscale.h"
#include <stdlib.h>
#include <err.h>

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path as argument");
    
    Image wow = load_image(argv[1]);
    grayscale(&wow);
    dilation(&wow);
    erosion(&wow);
    save_image(&wow, "result_morpho_ops.jpg");
    free_image(&wow);

    return 0;
}
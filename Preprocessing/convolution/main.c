#include <err.h>
#include "../tools/image.h"
#include "convolution.h"
#include "../grayscale/grayscale.h"

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path as argument");
    Image wow = load_image(argv[1]);
    //float kernel[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    //float kernel[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
    float kernel[9] = {0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11};
    //grayscale(&wow);
    convolution(&wow, kernel);
    save_image(&wow, "result_convolution.jpg");
    free_image(&wow);
    return 0;
}
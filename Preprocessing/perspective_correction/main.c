#include "perspective_correction.h"
#include "matrix_tools.h"
#include <stdio.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc != 2)
        errx(1, "Give an image path as argument");
    
    Image wow = load_image(argv[1]);
    int src[8] = {70, 65, 1940, 65, 2080, 1830, 40, 1900};
    correct_perspective(&wow, src);
    /*printf("width: %d and height: %d", wow.width, wow.height);
    wow.matrix[70][65] = (Pixel) {255, 0, 0}; //haut gauche
    wow.matrix[40][1900] = (Pixel) {255, 0, 0}; //bas gauche
    wow.matrix[1940][65] = (Pixel) {255, 0, 0}; //haut droite
    wow.matrix[2080][1830] = (Pixel) {255, 0, 0};*/ //bas droite
    save_image(&wow, "result_perspective.jpg");
    free_image(&wow);
    

    return 0;
}
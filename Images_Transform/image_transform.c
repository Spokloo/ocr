#include "image_transform.h"
#include "../Tools/image.h"
#include "include/rotate.h"
#include "include/perspective_correction.h"
#include <stdio.h>
#include <string.h>
#include <err.h>

int main(int argc, char **argv)
{
    if(argc != 2)
        errx(1, "Give an image path or 'all' as arguments");
    
    Image img = load_image(argv[1]);
    rotate(&img, 90);
    //int src[8] = {70, 65, 1940, 65, 2080, 1830, 40, 1900};
    //correct_perspective(&img, src);
    /*printf("width: %d and height: %d", img.width, img.height);
    img.matrix[70][65] = (Pixel) {255, 0, 0}; //haut gauche
    img.matrix[40][1900] = (Pixel) {255, 0, 0}; //bas gauche
    img.matrix[1940][65] = (Pixel) {255, 0, 0}; //haut droite
    img.matrix[2080][1830] = (Pixel) {255, 0, 0};*/ //bas droite
    save_image(&img, "result.jpg");
    free_image(&img);
    return 0;
}

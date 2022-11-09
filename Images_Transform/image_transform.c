#include "image_transform.h"
#include "../Tools/image.h"
#include "include/rotate.h"
#include "include/perspective_correction.h"
#include "include/split_grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

int main(int argc, char **argv)
{
    if(argc != 2)
        errx(1, "Give an image path or 'all' as arguments");
    
    Image img = load_image(argv[1]);

    //- - - - - - Rotate - - - - -
    //rotate(&img, 90);

    //- - - - Correct perspective - - - - - - 
    int src6[8] = {70, 65, 1940, 65, 2080, 1830, 40, 1900};
    int src5[8] = {630, 180, 1365, 695, 849, 1435, 110, 915};
    correct_perspective(&img, src5);

    // - - - Extract each cells - - - - -
    Image **cells = malloc(81 * sizeof(Image*));
    get_cells(&img, cells);
    char name[8] = "0i.jpeg";
    for(unsigned char i = 0; i < 81; i++)
    {
        if(i < 10)
            name[1] = i + '0';
        else
        {
            name[0] = i / 10 + '0';
            name[1] = i % 10 + '0';
        }
        save_image(cells[i], name);
        free_image(cells[i]);
        free(cells[i]);
    }
    free(cells);

    /*printf("width: %d and height: %d", img.width, img.height);
    img.matrix[630][180] = (Pixel) {255, 0, 0}; //haut gauche
    img.matrix[110][915] = (Pixel) {255, 0, 0}; //bas gauche
    img.matrix[849][1435] = (Pixel) {255, 0, 0}; //bas droite
    img.matrix[1365][695] = (Pixel) {255, 0, 0};*/ //haut droite
    save_image(&img, "result.jpeg");
    free_image(&img);
    return 0;
}

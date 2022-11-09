#include "image_processing.h"
#include "../Tools/image.h"
#include "include/grayscale.h"
#include "include/normalize.h"
#include "include/contrast.h"
#include "include/blur.h"
#include "include/morphological_ops.h"
#include "include/canny.h"
#include <stdio.h>
#include <string.h>
#include <err.h>

void apply_filters(char *path, char *newName)
{
    Image img = load_image(path);
    unsigned char filter_size = 0;
    if(img.width > img.height)
        filter_size = img.width / 300;
    else
        filter_size = img.height / 300;
    grayscale(&img);
    save_image(&img, "grayscale.jpeg");
    normalize(&img);
    save_image(&img, "normalize.jpeg");
    gaussian_blur(&img, filter_size);
    save_image(&img, "gaussian_blur.jpeg");
    dilation(&img, filter_size);
    save_image(&img, "dilation.jpeg");
    erosion(&img, filter_size);
    save_image(&img, "dilation+erosion.jpeg");
    canny(&img);
    save_image(&img, newName);
    free_image(&img);
}


void testall()
{
    char path[29] = "../Images_Test/image_00.jpeg";
    path[28] = '\0';
    char newName[21] = "result_image_00.jpeg";
    newName[20] = '\0';
    Image img;
    char images[4] = {1, 2, 3, 5};
    for(size_t i = 0; i < 4; i++)
    {
        path[22] = images[i] + '0';
        newName[14] = images[i] + '0';
        printf("Work on %s\n", path);
        img = load_image(path);
        unsigned char filter_size = 0;
        if(img.width > img.height)
            filter_size = img.width / 300;
        else
            filter_size = img.height / 300;
        grayscale(&img);
        normalize(&img);
        gaussian_blur(&img, filter_size);
        dilation(&img, filter_size);
        erosion(&img, filter_size);
        canny(&img);
        save_image(&img, newName);
        free_image(&img);

        printf("==============================\n");
    }
}

int main(int argc, char **argv)
{
    if(argc != 2)
        errx(1, "Give an image path or 'all' as arguments");
    if(strcmp(argv[1], "all") == 0)
        testall();
    else
        apply_filters(argv[1], "result.jpeg");
    return 0;
}

#include "contrast/contrast.h"
#include "grayscale/grayscale.h"
#include "canny/canny.h"
#include "tools/image.h"
#include "normalize/normalize.h"
#include "morphological_ops/morphological_ops.h"
#include "blur/blur.h"
#include <stdio.h>
#include <stdlib.h>
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
    printf("%d\n", filter_size);
    grayscale(&img);
    gaussian_blur(&img, filter_size);
    /*normalize(&img);
    dilation(&img);
    //erosion(&img);   
    canny(&img); */    
    save_image(&img, newName);
    
    free_image(&img);
}


void testall()
{
    char path[29] = "../Images_Test/image_00.jpeg";
    path[28] = '\0';
    char newName[21] = "result_image_00.jpeg";
    newName[20] = '\0';
    for(size_t i = 1; i <= 6; i++)
    {
        path[22] = i + '0';
        newName[14] = i + '0';
        printf("Work on %s\n", path);
        apply_filters(path, newName);
    }
}

int main(int argc, char **argv)
{
    if(strcmp(argv[1], "all") == 0)
        testall();
    else
    {
        if(argc != 2)
            errx(1, "Give an image path");
        apply_filters(argv[1], "result.jpg");
    }
    return 0;
}
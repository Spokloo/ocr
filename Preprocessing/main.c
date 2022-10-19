#include "contrast/contrast.h"
#include "grayscale/grayscale.h"
#include "canny/canny.h"
#include "tools/image.h"
#include "normalize/normalize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

void testall()
{
    Image img;
    char path[29] = "../Images_Test/image_00.jpeg";
    path[28] = '\0';
    char newName[21] = "result_image_00.jpeg";
    newName[20] = '\0';
    for(size_t i = 1; i <= 6; i++)
    {
        path[22] = i + '0';
        newName[14] = i + '0';
        printf("Work on %s\n", path);

        img = load_image(path);
        grayscale(&img);
        normalize(&img);
        canny(&img);        
        save_image(&img, newName);
        free_image(&img);
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
    
        Image img = load_image(argv[1]);
        grayscale(&img);
        canny(&img);
        save_image(&img, "result.jpg");
        free_image(&img);
    }
    return 0;
}
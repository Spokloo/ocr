#include "image_processing.h"
#include "grid_detection.h"
#include "nn.h"
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_help()
{
    printf("Usage : ./gridoku-ocr <image_path> [OPTIONS] or ./gridoku-ocr nn "
           "[OPTIONS]\n");

    printf("\nOptions ocr :\n");
    printf("    -o <path> : save the result into <path>\n");
    printf("    -v : print details of process\n");
    printf("    -s <folder> : save all intermediate image into <folder>\n");

    printf("\nOptions nn :\n");
    printf("    -train <folder> : train the neural network with images in "
           "<folder>\n");
    printf("    -test <image_path> : predict the number in image\n\n");

    errx(1, "Wrong arguments.");
}

void nn_args(int argc, char **argv)
{
    if (argc == 2)
        print_help();
    if (strcmp(argv[2], "train") == 0 && argc == 4)
        train_neural_network(argv[3]);
    else if (strcmp(argv[2], "test") == 0 && argc == 4)
        test_neural_network(argv[3]);
    else
        print_help();
}

void img_args(int argc, char **argv)
{
    // parse arguments
    int opt;
    char out = 0, save_inter = 0, verbose = 0;
    char *out_path = NULL, *inter_path = NULL;
    char *img_path = argv[1];
    while ((opt = getopt(argc, argv, "o:vs:")) != -1)
    {
        switch (opt)
        {
        case 'o':
            out = 1;
            out_path = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 's':
            save_inter = 1;
            inter_path = optarg;
            break;
        case '?':
            print_help();
            break;
        }
    }
    if (optind >= argc)
        print_help();

    char tmppath[128];
    unsigned int n = strlen(inter_path);
    if (save_inter)
    {
        strncpy(tmppath, inter_path, n);
        tmppath[n] = '/';
    }
    Image img = load_image(img_path);

    // - - - - - - - - - - PREPROCESSING - - - - - - - - - -
    unsigned char filter_size = 0;
    if (img.width > img.height)
        filter_size = img.width / 300;
    else
        filter_size = img.height / 300;

    grayscale(&img);
    if (verbose)
        printf("Grayscale image ...\n");
    if (save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "1.0-grayscale.png");
        save_image(&img, tmppath);
    }
    normalize(&img);
    if (verbose)
        printf("Normalize image ...\n");
    if (save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "1.1-normalize.png");
        save_image(&img, tmppath);
    }
    gaussian_blur(&img, filter_size);
    if (verbose)
        printf("Gaussian blur image ...\n");
    if (save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "1.2-gaussian_blur.png");
        save_image(&img, tmppath);
    }
    dilation(&img, filter_size);
    if (verbose)
        printf("Dilation image ...\n");
    if (save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "1.3-dilation.png");
        save_image(&img, tmppath);
    }
    erosion(&img, filter_size);
    if (verbose)
        printf("Erosion image ...\n");
    if (save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "1.4-dilation_erosion.png");
        save_image(&img, tmppath);
    }
    canny(&img);
    if (verbose)
        printf("Canny image ...\n");
    if (save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "1.5-canny.png");
        save_image(&img, tmppath);
    }

    // - - - - - - - - - - GRID DETECTION - - - - - - - - - -


    // - - - - - - - - - - POST GRID PROCESSING - - - - - - - - - -

    // - - - - - - - - - - NEURAL NETWORK - - - - - - - - - -

    // - - - - - - - - - - SOLVER - - - - - - - - - -

    // - - - - - - - - - - SOLVED GRID GENERATION - - - - - - - - - -

    // - - - - - - - - - - FINAL SAVE - - - - - - - - - -
    if(save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "result.png");
        save_image(&img, tmppath);
    }
    else if (out)
    {
        tmppath[0] = '\0';
        n = strlen(out_path);
        strncpy(tmppath, out_path, n);
        tmppath[n] = '/';
        strcat(tmppath, "result.png");
        save_image(&img, tmppath);
    }
    else
        save_image(&img, "./result.png");
    free_image(&img);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        print_help();

    // Neural Network
    if (strcmp(argv[1], "nn") == 0)
        nn_args(argc, argv);
    else
        img_args(argc, argv);
    return 0;
}

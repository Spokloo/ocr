#include "image_processing.h"
#include "grid_detection.h"
#include "images_post_grid.h"
#include "nn.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
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
    Image copy_img;
    copy_image(&img, &copy_img);

    int **real_lines = NULL;
    unsigned int lines_len = 0;
    Square *sq = NULL;
    Square *gs = NULL;

    Image **result_imgs = malloc(sizeof(Image*) * 5);
    for (int i = 0; i < 5; i++)
        result_imgs[i] = NULL;

    if(verbose)
        printf("Hough transform...\n");
    hough_transform(&img, &lines_len, &real_lines);
    result_imgs[0] = &img;
    if(save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "2.0-hough_lines.png");
        save_image(&img, tmppath);
    }

    auto_rotation(&img, &copy_img, &lines_len, &real_lines, &result_imgs);
    if(verbose && result_imgs[1] != NULL)
        printf("Auto-rotation...\n");
    if(save_inter && result_imgs[1] != NULL)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "2.1-auto_rotate.png");
        save_image(&img, tmppath);
    }

    if(verbose)
    {
        printf("Detecting all squares...\n");
        printf("Getting the grid square...\n");
    }
    squares(&img, &lines_len, &real_lines, &sq, &gs, &result_imgs);
    if(save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "2.2-all_squares.png");
        save_image(result_imgs[2], tmppath);
        tmppath[n+1] = '\0';
        strcat(tmppath, "2.3-main_grid_detection.png");
        save_image(&img, tmppath);
    }

    if(verbose)
        printf("Correcting perspective...\n");
    int points[8] = { gs->p1.x, gs->p1.y, gs->p2.x, gs->p2.y,
        gs->p3.x, gs->p3.y, gs->p4.x, gs->p4.y };
    correct_perspective(&img, points);
    if(save_inter)
    {
        tmppath[n+1] = '\0';
        strcat(tmppath, "2.4-corrected_perspective.png");
        save_image(&img, tmppath);
    }

    for (unsigned int i = 0; i < lines_len; i++)
        free(real_lines[i]);
    free(real_lines);
    free_image(result_imgs[2]);
    free(result_imgs[2]);
    free(result_imgs);
    free(sq);

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

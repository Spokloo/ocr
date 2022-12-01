#include "nn.h"
#include "nn_tools.h"
#include "nn_load_data.h"
#include "weights.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help()
{
    printf("Neural Network usage:\n");
    printf("    - ./neural_network train folder_path\n");
    printf("    - ./neural_network test image_path\n");
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        print_help();
        return -1;
    }
    printf("\e[?25l"); //hide cursor

    NeuralNetwork nn = new_nn();

    load_weights(&nn);

    if (strcmp(argv[1], "train") == 0)
    {
        NnDatas data = load_training_images(argv[2]);
        train(&nn, &data);
        free_data(&data);
    }
    else if (strcmp(argv[1], "test") == 0)
    {
        Image img = load_image(argv[2]);
        char *input = image_to_int(&img);
        printf("%d\n", get_output(&nn, input, 0));
        free_image(&img);
        free(input);
    }
    else
    {
        print_help();
        return -1;
    }

    printf("\e[?25h"); //reshow cursor

    save_weights(&nn);

    free_nn(&nn);

    return 0;
}
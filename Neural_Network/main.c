#include "nn.h"
#include "nn_load_data.h"
#include "nn_tools.h"
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

void test_mnist(NeuralNetwork *nn)
{
    NnDatas data = load_training_images("../../MNIST/testing");
    printf("\n");
    double precision = 0;
    char max;
    unsigned long sucess = 0;
    for (unsigned int ex = 0; ex < data.max_ex; ex++)
    {
        // for example n°ex of each numbers
        for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++)
        {
            max = get_output(nn, data.input[nb], ex * NB_INPUT);
            // only for precision
            if (max - nb == 0)
                sucess++;

            precision = sucess / (float)data.total;
            // printf("Give : %d and received %f\n", nb, max);
            printf("\rTesting -> %.2f%% (%ld / %ld)", precision * 100, sucess,
                   data.total);
        }
    }
    printf("\n");
    free_data(&data);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        print_help();
        return -1;
    }

    NeuralNetwork nn = new_nn();

    load_weights(&nn, "weights");

    if (strcmp(argv[1], "train") == 0)
    {
        NnDatas data = load_training_images(argv[2]);
        printf("\e[?25l"); // hide cursor
        train(&nn, &data);
        free_data(&data);
        // test_mnist(&nn);
        printf("\e[?25h"); // reshow cursor
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

    save_weights(&nn, "weights");

    free_nn(&nn);

    return 0;
}
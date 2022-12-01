<<<<<<< HEAD:Neural_Network/nn_tools.c
#include "nn_tools.h"
#include "../Tools/image.h"
=======
#include "../include/nn_tools.h"
<<<<<<< HEAD
>>>>>>> 91e96214fcd9fe662c3bb8a9eb91d30c90d7b4b6:Neural_Network/source/nn_tools.c
=======
#include "../../Tools/image.h"
>>>>>>> e306382875effd7e72ef5681afcf5cee5626be3d
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Create a new Neural Network depending on constants in nn.h.
 */
NeuralNetwork new_nn()
{
    // init variables
    NeuralNetwork nn;
    unit *u = NULL;
    unit **input_l = NULL;
    double *input_w = NULL;

    // input layer
    for (unsigned int i = 0; i < NB_INPUT; i++)
    {
        u = malloc(sizeof(unit));
        *u = (unit){0, 0, 0, NULL, NULL};
        nn.input[i] = u;
    }

    // hidden layer
    for (unsigned int i = 0; i < NB_HIDDEN; i++)
    {
        input_l = malloc(NB_INPUT * sizeof(unit *));
        input_w = malloc(NB_INPUT * sizeof(double));
        for (int j = 0; j < NB_INPUT; j++)
        {
            input_l[j] = nn.input[j];
            input_w[j] = generate_weigth(NB_INPUT);
        }
        u = malloc(sizeof(unit));
        *u = (unit){1, generate_weigth(NB_INPUT), NB_INPUT, input_l, input_w};
        nn.hidden[i] = u;
    }

    // output layer
    for (unsigned int i = 0; i < NB_OUTPUT; i++)
    {
        input_l = malloc(NB_HIDDEN * sizeof(unit *));
        input_w = malloc(NB_HIDDEN * sizeof(double));
        for (unsigned int j = 0; j < NB_HIDDEN; j++)
        {
            input_l[j] = nn.hidden[j];
            input_w[j] = generate_weigth(NB_HIDDEN);
        }
        u = malloc(sizeof(unit));
        *u = (unit){1, generate_weigth(NB_HIDDEN), NB_HIDDEN, input_l, input_w};
        nn.output[i] = u;
    }
    return nn;
}

/*
 * Randomly generate a number betwenn -2.4/nb_input and 2.4/nb_input.
 */
double generate_weigth(int nb_input)
{
    double max = 2.4 / nb_input;
    double min = -2.4 / nb_input;
    double a = (double)RAND_MAX;
    double div = a / (max - min);
    int random = rand();
    return min + (random / div);
}

/*
 * Free all memory used by a NeuralNetwork.
 */
void free_nn(NeuralNetwork *nn)
{
    for (unsigned int i = 0; i < NB_INPUT; i++)
    {
        free(nn->input[i]);
    }
    for (unsigned int i = 0; i < NB_HIDDEN; i++)
    {
        free(nn->hidden[i]->inputlinks);
        free(nn->hidden[i]->inputweights);
        free(nn->hidden[i]);
    }
    for (unsigned int i = 0; i < NB_OUTPUT; i++)
    {
        free(nn->output[i]->inputlinks);
        free(nn->output[i]->inputweights);
        free(nn->output[i]);
    }
}

/*
 * Print a unit with value, biais and weights.
 */
void print_unit(unit *n)
{
    printf("value : %f\n", n->value);
    printf("bias : %f\n", n->bias);
    printf("nbinput : %d\n", n->nb_input);
    for (unsigned int i = 0; i < n->nb_input; i++)
        printf("value : %f and weight : %f\n", n->inputlinks[i]->value,
               n->inputweights[i]);
}

/*
 * Print each unit of the Neural Network with value, biais and weights.
 */
void print_nn(NeuralNetwork *nn)
{
    for (unsigned int i = 0; i < NB_OUTPUT; i++)
    {
        printf("output n°%d : \n", i);
        print_unit(nn->output[i]);
        printf("\n");
    }
    for (unsigned int i = 0; i < NB_HIDDEN; i++)
    {
        printf("hidden n°%d: \n", i);
        print_unit(nn->hidden[i]);
        printf("\n");
    }
    for (unsigned int i = 0; i < NB_INPUT; i++)
    {
        printf("input n°%d : \n", i);
        print_unit(nn->input[i]);
        printf("\n");
    }
}

<<<<<<< HEAD
char *im_to_int(Image *im)
{
    char *res= malloc(784*sizeof(char));
    int ind=0;
    for (int i=0;i<28;i++)
    {
        for (int j=0;j<28;j++)
        {
            res[ind]=im->matrix[i][j].r/255;
            ind++;
        }
    }
=======
/*
 * Convert an image at path to a 1D array of 0 and 1.
 */
char *image_to_int(char *path)
{
    Image im = load_image(path);
    if(im.height != 28 || im.width != 28)
        errx(1, "Wrong image format. It should be 28*28 pixels.");
    unsigned int index = 0;
    char *res = malloc(784 * sizeof(char));
    for (unsigned char i = 0; i < 28; i++)
    {
        for (unsigned char j = 0; j < 28; j++)
        {
            res[index] = im.matrix[j][i].r / 255;
            index++;
        }
    }
    free_image(&im);
>>>>>>> e306382875effd7e72ef5681afcf5cee5626be3d
    return res;
}

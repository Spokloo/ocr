#include "xor_tools.h"
#include "xor.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Create a structure Neural network which can compute a xor.
 */
NeuralNetwork new_xor()
{
    // input layer
    unit *x = malloc(sizeof(unit));
    *x = (unit){1, 0, 0, NULL, NULL};
    unit *y = malloc(sizeof(unit));
    *y = (unit){0, 0, 0, NULL, NULL};

    // hidden layer
    unit **input_l_h = malloc(2 * sizeof(unit *));
    input_l_h[0] = x;
    input_l_h[1] = y;
    double *input_w_h = malloc(2 * sizeof(double));
    input_w_h[0] = 0;
    input_w_h[1] = 0;
    unit *h = malloc(sizeof(unit));
    *h = (unit){0, 0, 2, input_l_h, input_w_h};

    // output layer
    unit **inputz = malloc(3 * sizeof(unit *));
    inputz[0] = x;
    inputz[1] = h;
    inputz[2] = y;
    double *input_w_z = malloc(3 * sizeof(double));
    input_w_z[0] = 0;
    input_w_z[1] = 0;
    input_w_z[2] = 0;
    unit *z = malloc(sizeof(unit));
    *z = (unit){0, 0, 3, inputz, input_w_z};

    NeuralNetwork xor = {{x, y}, {h}, {z}};
    return xor;
}

/*
 * Free memory allocated when create a xor network.
 */
void free_xor(NeuralNetwork xor)
{
    free(xor.input[0]);
    free(xor.input[1]);
    free(xor.hidden[0]->inputlinks);
    free(xor.hidden[0]->inputweights);
    free(xor.hidden[0]);
    free(xor.output[0]->inputlinks);
    free(xor.output[0]->inputweights);
    free(xor.output[0]);
}

void print_xor_unit(unit *n)
{
    printf("value : %f\n", n->value);
    printf("bias : %f\n", n->bias);
    printf("nbinput : %d\n", n->nb_input);
    for (int i = 0; i < n->nb_input; i++)
        printf("value : %f and weight : %f\n", n->inputlinks[i]->value,
               n->inputweights[i]);
}

void print_xor(NeuralNetwork xor)
{
    printf("z : \n");
    print_xor_unit(xor.output[0]);
    printf("h : \n");
    print_xor_unit(xor.hidden[0]);
    printf("x : \n");
    print_xor_unit(xor.input[0]);
    printf("y : \n");
    print_xor_unit(xor.input[1]);
}
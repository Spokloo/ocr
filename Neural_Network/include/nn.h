#ifndef NN_H
#define NN_H

#define LEARNRATE 0.1
#define NB_INPUT 784
#define NB_HIDDEN 15
#define NB_OUTPUT 10
#define NB_TRAINING_SET 10

typedef struct unit
{
    double value;
    double bias;
    unsigned int nb_input;
    struct unit **inputlinks;
    double *inputweights;
} unit;

typedef struct NeuralNetwork
{
    unit *input[NB_INPUT];
    unit *hidden[NB_HIDDEN];
    unit *output[NB_OUTPUT];
} NeuralNetwork;

typedef struct NnDatas
{
    char **input;
    char **expected;
    unsigned int max_ex;
    unsigned long total;
} NnDatas;

#include "nn_tools.h"
#include "nn_load_data.h"
#include "weights.h"

/*
 * Training of the Neural Network with input values and expected results until
 * precision is reached.
 */
void train(NeuralNetwork *nn, NnDatas *data);

/*
 * Give input array to the Neural Network and return its result.
 */
char get_output(NeuralNetwork *nn, char *input, unsigned long shift);

/*
 * Compute the new value of u depending on its links and weights.
 */
void activation(unit *u);

/*
 * Activate function used to compute value of each neuron.
 */
double activate_function(double n);

/*
 * Train nn from A to Z.
 */
void train_neural_network(char *path);

/*
 * Test nn on an image.
 */
void test_neural_network(char *path);

#endif

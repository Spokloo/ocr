#ifndef NN_H
#define NN_H

#define LEARNRATE 0.01
#define NB_INPUT 784
#define NB_HIDDEN 50
#define NB_OUTPUT 10
#define NB_TRAINING_SET 5

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
    unsigned int size;
} NnDatas;

/*
 * Training of the Neural Network with input values and expected results until
 * precision is reached. Return the number of epoch.
 */
unsigned long train(NeuralNetwork *nn, NnDatas *data);

/*
 * Give input array to the Neural Network and return its result.
 */
double get_output(NeuralNetwork *nn, char *input, unsigned long shift);

/*
 * Compute the new value of u depending on its links and weights.
 */
void activation(unit *u);

/*
 * Activate function used to compute value of each neuron.
 */
double activate_function(double n);

#endif
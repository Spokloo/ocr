#ifndef NN_H
#define NN_H

#define LEARNRATE 2
#define NB_INPUT 2
#define NB_HIDDEN 2
#define NB_OUTPUT 1
#define NB_TRAINING_SET 4

typedef struct unit
{
    double value;
    double bias;
    unsigned char nb_input;
    struct unit **inputlinks;
    double *inputweights;
} unit;

typedef struct NeuralNetwork
{
    unit *input[NB_INPUT];
    unit *hidden[NB_HIDDEN];
    unit *output[NB_OUTPUT];
} NeuralNetwork;

/*
 * Training of the Neural Network with input values and expected results until
 * precision is reached. Return the number of epoch.
 */
unsigned long train(NeuralNetwork *nn, char input[NB_TRAINING_SET][NB_INPUT],
                    char expected[NB_TRAINING_SET][NB_OUTPUT],
                    double precision);

/*
 * Give input array to the Neural Network and return its result.
 */
double get_output(NeuralNetwork *nn, char input[NB_INPUT]);

/*
 * Compute the new value of u depending on its links and weights.
 */
void activation(unit *u);

/*
 * Activate function used to compute value of each neuron.
 */
double activate_function(double n);

#endif

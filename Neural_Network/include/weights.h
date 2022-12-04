#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "nn.h"

/*
 * Save all weights of a neural network in a file 'weights' in current
 * directory.
 */
void save_weights(NeuralNetwork *nn, char *path);

/*
 * Load all weights saved in a file 'weights' (if exists) to the neural network.
 * Throw an error if the 'weights' file is invalid.
 */
void load_weights(NeuralNetwork *nn, char *path);

#endif
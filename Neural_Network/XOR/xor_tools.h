#ifndef XOR_TOOLS_H
#define XOR_TOOLS_H

#include "xor.h"

/*
 * Create a structure Neural network which can compute a xor.
 */
NeuralNetwork new_xor();

/*
 * Free memory allocated when create a xor network.
 */
void free_xor(NeuralNetwork xor);

void print_unit(unit *n);

void print_xor(NeuralNetwork xor);

/*
 * Save all weights of a neural network in a file 'weights' in current
 * directory.
 */
void save_weights(NeuralNetwork xor);

/*
 * Load all weights saved in a file 'weights' (if exists) to the neural network.
 * Throw an error if the 'weights' file is invalid.
 */
void load_weights(NeuralNetwork nn);

#endif
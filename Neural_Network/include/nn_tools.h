#ifndef NN_TOOLS_H
#define NN_TOOLS_H

#include "../../Tools/image.h"
#include "../nn.h"

/*
 * Create a new Neural Network depending on constants in nn.h.
 */
NeuralNetwork new_nn();

/*
 * Randomly generate a number betwenn -2.4/nb_input and 2.4/nb_input.
 */
double generate_weigth(int nb_next);

/*
 * Free all memory used by a NeuralNetwork.
 */
void free_nn(NeuralNetwork *nn);

/*
 * Print a unit with value, biais and weights.
 */
void print_unit(unit *n);

/*
 * Print each unit of the Neural Network with value, biais and weights.
 */
void print_nn(NeuralNetwork *nn);

/*
 * Convert an image at path to a 1D array of 0 and 1.
 */
char *image_to_int(char *path);

#endif

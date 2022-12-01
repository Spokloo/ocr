#ifndef NN_TOOLS_H
#define NN_TOOLS_H

<<<<<<< HEAD:Neural_Network/nn_tools.h
#include "nn.h"
#include "../Tools/image.h"
=======
#include "../nn.h"

>>>>>>> 91e96214fcd9fe662c3bb8a9eb91d30c90d7b4b6:Neural_Network/include/nn_tools.h
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
 * transform an binarized image to unidimensional matrix
 */

<<<<<<< HEAD
char *im_to_int (Image *im);
#endif
=======
/*
 * Convert an image at path to a 1D array of 0 and 1.
 */
char *image_to_int(char *path);

#endif
>>>>>>> e306382875effd7e72ef5681afcf5cee5626be3d

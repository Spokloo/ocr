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

void print_xor_unit(unit *n);

void print_xor(NeuralNetwork xor);

#endif
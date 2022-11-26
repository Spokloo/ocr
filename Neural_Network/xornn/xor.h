#ifndef XOR_H
#define XOR_H

#define LEARNRATE 2
#define NB_INPUT 2
#define NB_HIDDEN 2
#define NB_OUTPUT 1

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

void update_activate_value(unit *u);
void activate(unit *u);
double calculate_expected(int i1, int i2);

#endif

#include "nn_tools.h"
#include "weights.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    NeuralNetwork nn = new_nn();
    load_weights(&nn);

    char input[NB_TRAINING_SET][NB_INPUT] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    char expected[NB_TRAINING_SET][NB_OUTPUT] = {{0}, {1}, {1}, {0}};

    unsigned long epoch = train(&nn, input, expected, 0.01);

    double res;
    printf("%ld epoch : \n", epoch);
    for (unsigned int i = 0; i < NB_TRAINING_SET; i++)
    {
        res = get_output(&nn, input[i]);
        printf("%d and %d -> %f (%d)\n", input[i][0], input[i][1], res,
               expected[i][0]);
    }
    // print_nn(&nn);
    save_weights(&nn);
    free_nn(&nn);
    return 0;
}

/*
 * Training of the Neural Network with input values and expected results until
 * precision is reached. Return the number of epoch.
 */
unsigned long train(NeuralNetwork *nn, char input[NB_TRAINING_SET][NB_INPUT],
                    char expected[NB_TRAINING_SET][NB_OUTPUT], double precision)
{
    double grad = 1, val = 0, diff = 1, err, sum;
    double delta[NB_HIDDEN + 1];
    double delta2[NB_INPUT * NB_HIDDEN + NB_HIDDEN];
    double grad_output[NB_OUTPUT];
    unsigned int delta_i = 0;
    unsigned long epoch = 0;
    while (diff > precision)
    {
        diff = 0;
        for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++)
        {
            // Give example
            for (unsigned int i = 0; i < NB_INPUT; i++)
                nn->input[i]->value = input[nb][i];

            // Update activate value of hidden and output layer
            for (unsigned int i = 0; i < NB_HIDDEN; i++)
                activation(nn->hidden[i]);
            for (unsigned int i = 0; i < NB_OUTPUT; i++)
                activation(nn->output[i]);

            // Compute expected
            printf("%.f and %.f -> %f (%d)\n", nn->input[0]->value,
                   nn->input[1]->value, nn->output[0]->value, expected[nb][0]);

            // Compute weights correction between hidden and output
            for (unsigned int i = 0; i < NB_OUTPUT; i++)
            {
                // Compute error between example and output
                val = nn->output[i]->value;
                err = expected[nb][i] - val;
                diff += (err * err); // only for precision
                grad = err * val * (1.0 - val);
                grad_output[i] = grad;

                for (unsigned int j = 0; j < nn->output[i]->nb_input; j++)
                    delta[j] = LEARNRATE * nn->hidden[j]->value * grad;
                delta[NB_HIDDEN] = LEARNRATE * grad; // biais
            }

            // Compute weights correction between input and hidden
            delta_i = 0;
            for (unsigned int i = 0; i < NB_HIDDEN; i++, delta_i++)
            {
                // Compute sum of grad_output * inputweights
                sum = 0;
                for (unsigned int j = 0; j < NB_OUTPUT; j++)
                    sum += grad_output[j] * nn->output[j]->inputweights[i];

                val = nn->hidden[i]->value;
                grad = val * (1.0 - val) * sum;

                for (unsigned int j = 0; j < nn->hidden[i]->nb_input;
                     j++, delta_i++)
                    delta2[delta_i] = LEARNRATE * nn->input[j]->value * grad;

                delta2[delta_i] = LEARNRATE * grad; // biais
            }

            // Update weights betweenn hidden and output
            for (unsigned int i = 0; i < nn->output[0]->nb_input; i++)
                nn->output[0]->inputweights[i] += delta[i];
            nn->output[0]->bias += delta[NB_HIDDEN];

            // Update weights betweenn input and hidden
            delta_i = 0;
            for (unsigned int i = 0; i < NB_HIDDEN; i++, delta_i++)
            {
                for (unsigned int j = 0; j < nn->hidden[i]->nb_input;
                     j++, delta_i++)
                    nn->hidden[i]->inputweights[j] += delta2[delta_i];
                nn->hidden[i]->bias += delta2[delta_i];
            }
        }
        epoch++;
    }
    return epoch;
}

/*
 * Give input array to the Neural Network and return its result.
 */
double get_output(NeuralNetwork *nn, char input[NB_INPUT])
{
    for (unsigned int i = 0; i < NB_INPUT; i++)
        nn->input[i]->value = input[i];

    for (unsigned int i = 0; i < NB_HIDDEN; i++)
        activation(nn->hidden[i]);
    for (unsigned int i = 0; i < NB_OUTPUT; i++)
        activation(nn->output[i]);

    double max = nn->output[0]->value, val;
    unsigned int index = 0;
    for (unsigned int i = 1; i < NB_OUTPUT; i++)
    {
        val = nn->output[i]->value;
        if (val > max)
        {
            max = val;
            index = i;
        }
    }
    // return index; // when image
    return max;
}

/*
 * Compute the new value of u depending on its links and weights.
 */
void activation(unit *u)
{
    double res = 0;
    for (unsigned char i = 0; i < u->nb_input; i++)
        res += u->inputlinks[i]->value * u->inputweights[i];
    res += u->bias;
    u->value = activate_function(res);
}

/*
 * Activate function used to compute value of each neuron.
 */
double activate_function(double n)
{
    return 1 / (1 + exp(-n));
}

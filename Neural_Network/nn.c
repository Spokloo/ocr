#include "include/nn_load_data.h"
#include "include/nn_tools.h"
#include "include/weights.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    NeuralNetwork nn = new_nn();
    //load_weights(&nn);
    printf("NN created\n");
    NnDatas data = load_training_images("training_test");
    printf("Datas loaded\n");
    unsigned long epoch = train(&nn, &data);

    double res;
    printf("\n%ld epoch : \n", epoch);
    for (unsigned int ex = 0; ex < data.size; ex++)
    {
        for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++)
        {
            res = get_output(&nn, data.input[nb], ex * NB_INPUT);
            printf("Give : %d and received %f\n", nb, res);
        }
    }
    /*for (unsigned int ex = 0; ex < data.size; ex++)
    {
        for (unsigned int i = 0; i < NB_TRAINING_SET; i++)
        {
            printf("%d : \n", i);
            for (unsigned int j = 0; j < NB_OUTPUT; j++)
            {
                printf("%d ", data.expected[i][ex * 10 + j]);
            }
            printf("\n");
        }
    }*/
    free_data(&data);

    // print_nn(&nn);
    //save_weights(&nn);
    free_nn(&nn);
    return 0;
}

/*
 * Training of the Neural Network with input values and expected results until
 * precision is reached. Return the number of epoch.
 */
unsigned long train(NeuralNetwork *nn, NnDatas *data)
{
    double grad = 1, val = 0, diff = 0, err, sum;
    double delta[NB_HIDDEN + 1];
    double delta2[NB_INPUT * NB_HIDDEN + NB_HIDDEN];
    double grad_output[NB_OUTPUT];
    unsigned int delta_i = 0;
    unsigned long epoch = 0;
    double tmp = 0, tmp2 = 0, max = 0;
    while (diff != 1)
    {
        diff = 1;
        for (unsigned int ex = 0; ex < data->size; ex++)
        { // foreach exaemplary of numbers
            for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++)
            { // for example n°ex of each numbers
                //printf("ex n°%d with nb°%d\n", ex, nb);

                // Give example
                for (unsigned int i = 0; i < NB_INPUT; i++)
                {
                    nn->input[i]->value = data->input[nb][ex * NB_INPUT + i];
                    //printf("%.f ", nn->input[i]->value);
                }
                //printf("\n");

                // Update activate value of hidden and output layer
                for (unsigned int i = 0; i < NB_HIDDEN; i++)
                    activation(nn->hidden[i]);
                for (unsigned int i = 0; i < NB_OUTPUT; i++)
                    activation(nn->output[i]);

                // Print given and received
                tmp2 = nn->output[0]->value;
                max = 0;
                for (unsigned char i = 1; i < NB_OUTPUT; i++)
                {
                    tmp = nn->output[i]->value;
                    //printf("%f ", tmp);
                    if (tmp > tmp2)
                    {
                        tmp2 = tmp;
                        max = i;
                    }
                }
                printf("Give : %d and received %f\n", nb, max);
                diff = (max - nb == 0) && diff; // only for precision
                // Compute weights correction between hidden and output
                for (unsigned int i = 0; i < NB_OUTPUT; i++)
                {
                    // Compute error between example and output
                    val = nn->output[i]->value;
                    err = data->expected[nb][ex * NB_OUTPUT + i] - val;
                    //printf("%d ", data->expected[nb][ex * NB_OUTPUT + i]);
                    grad = err * val * (1.0 - val);
                    grad_output[i] = grad;

                    for (unsigned int j = 0; j < nn->output[i]->nb_input; j++)
                        delta[j] = LEARNRATE * nn->hidden[j]->value * grad;
                    delta[NB_HIDDEN] = LEARNRATE * grad; // biais
                }
                //printf("\n");

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
                        delta2[delta_i] =
                            LEARNRATE * nn->input[j]->value * grad;

                    delta2[delta_i] = LEARNRATE * grad; // biais
                }

                // Update weights betweenn hidden and output
                for (unsigned int i = 0; i < NB_OUTPUT; i++)
                {
                    for (unsigned int j = 0; j < nn->output[i]->nb_input; j++)
                        nn->output[i]->inputweights[j] += delta[j];
                    nn->output[i]->bias += delta[NB_HIDDEN];
                }

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
        }
        epoch++;
    }
    return epoch;
}

/*
 * Give input array to the Neural Network and return its result.
 */
double get_output(NeuralNetwork *nn, char *input, unsigned long shift)
{
    for (unsigned int i = 0; i < NB_INPUT; i++)
        nn->input[i]->value = input[i + shift];

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
    return index; // when image
    // return max;
}

/*
 * Compute the new value of u depending on its links and weights.
 */
void activation(unit *u)
{
    double res = 0;
    for (unsigned int i = 0; i < u->nb_input; i++)
        res += u->inputlinks[i]->value * u->inputweights[i];
    res += u->bias;
    u->value = activate_function(res);
}

/*
 * Activate function used to compute value of each neuron.
 */
double activate_function(double n)
{
    /*if(n > 0)
        return n;
    else
        return 0.01*n;*/
    return 1 / (1 + exp(-n));
}

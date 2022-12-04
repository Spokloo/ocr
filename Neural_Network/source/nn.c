#include "nn.h"
#include "nn_load_data.h"
#include "nn_tools.h"
#include "weights.h"
#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Training of the Neural Network with input values and expected results until
 * precision is reached.
 */
void train(NeuralNetwork *nn, NnDatas *data)
{
    double grad = 1, val = 0, err, sum, tmp = 0, tmp2 = 0, max = 0,
           precision = 1;
    double delta_output[NB_OUTPUT * NB_HIDDEN + NB_OUTPUT];
    double delta_hidden[NB_INPUT * NB_HIDDEN + NB_HIDDEN];
    double grad_output[NB_OUTPUT];
    unsigned int delta_output_i = 0, delta_hidden_i = 0;
    unsigned long epoch = 0, sucess = 0;
    // after 10 correct iterations on each example, stop
    while ((sucess == 0 || precision < 0.95) && epoch < 10)
    {
        sucess = 0;
        epoch++;
        // foreach exaemplary of numbers
        for (unsigned int ex = 0; ex < data->max_ex; ex++)
        {
            // for example n°ex of each numbers
            for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++)
            {
                // Give example
                for (unsigned int i = 0; i < NB_INPUT; i++)
                    nn->input[i]->value = data->input[nb][ex * NB_INPUT + i];

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
                    // printf("%f ", tmp);
                    if (tmp > tmp2)
                    {
                        tmp2 = tmp;
                        max = i;
                    }
                }
                // only for precision
                if (max - nb == 0)
                    sucess++;

                precision = sucess / (float)data->total;
                // printf("Give : %d and received %f\n", nb, max);
                printf("\rEpoch n°%ld -> %.2f%% (%ld / %ld)", epoch,
                       precision * 100, sucess, data->total);

                // Compute weights correction between hidden and output
                delta_output_i = 0;
                for (unsigned int i = 0; i < NB_OUTPUT; i++, delta_output_i++)
                {
                    // Compute error between example and output
                    val = nn->output[i]->value;
                    err = data->expected[nb][i] - val;
                    grad = err * val * (1.0 - val);
                    grad_output[i] = grad;

                    for (unsigned int j = 0; j < nn->output[i]->nb_input;
                         j++, delta_output_i++)
                        delta_output[delta_output_i] =
                            LEARNRATE * nn->hidden[j]->value * grad;
                    delta_output[delta_output_i] = LEARNRATE * grad; // biais
                }

                // Compute weights correction between input and hidden
                delta_hidden_i = 0;
                for (unsigned int i = 0; i < NB_HIDDEN; i++, delta_hidden_i++)
                {
                    // Compute sum of grad_output * inputweights
                    sum = 0;
                    for (unsigned int j = 0; j < NB_OUTPUT; j++)
                        sum += grad_output[j] * nn->output[j]->inputweights[i];

                    val = nn->hidden[i]->value;
                    grad = val * (1.0 - val) * sum;

                    for (unsigned int j = 0; j < nn->hidden[i]->nb_input;
                         j++, delta_hidden_i++)
                        delta_hidden[delta_hidden_i] =
                            LEARNRATE * nn->input[j]->value * grad;

                    delta_hidden[delta_hidden_i] = LEARNRATE * grad; // biais
                }

                // Update weights betweenn hidden and output
                delta_output_i = 0;
                for (unsigned int i = 0; i < NB_OUTPUT; i++, delta_output_i++)
                {
                    for (unsigned int j = 0; j < nn->output[i]->nb_input;
                         j++, delta_output_i++)
                        nn->output[i]->inputweights[j] +=
                            delta_output[delta_output_i];
                    nn->output[i]->bias += delta_output[delta_output_i];
                }

                // Update weights betweenn input and hidden
                delta_hidden_i = 0;
                for (unsigned int i = 0; i < NB_HIDDEN; i++, delta_hidden_i++)
                {
                    for (unsigned int j = 0; j < nn->hidden[i]->nb_input;
                         j++, delta_hidden_i++)
                        nn->hidden[i]->inputweights[j] +=
                            delta_hidden[delta_hidden_i];
                    nn->hidden[i]->bias += delta_hidden[delta_hidden_i];
                }
            }
        }
        printf("\n");
    }
    printf("\nEnd of training :\n");
    printf("    - %ld epoch \n", epoch);
    printf("    - %.2f%% of precision (%ld / %ld)\n", precision * 100, sucess,
           data->total);
}

/*
 * Give input array to the Neural Network and return its result.
 */
char get_output(NeuralNetwork *nn, char *input, unsigned long shift)
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

/*
 * Train nn from A to Z.
 */
void train_neural_network(char *path, char *weights_path)
{
    NeuralNetwork nn = new_nn();
    NnDatas data = load_training_images(path);
    printf("\e[?25l"); // hide cursor
    train(&nn, &data);
    free_data(&data);
    printf("\e[?25h"); // reshow cursor
    save_weights(&nn, weights_path);
    free_nn(&nn);
}

/*
 * Test nn on an image.
 */
void test_neural_network(char *path)
{
    NeuralNetwork nn = new_nn();
    load_weights(&nn, "weights");
    Image img = load_image(path);
    char *input = image_to_int(&img);
    printf("%d\n", get_output(&nn, input, 0));
    free_image(&img);
    free(input);
    free_nn(&nn);
}
#include "weights.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Save all weights of a neural network in a file 'weights' in current
 * directory.
 */
void save_weights(NeuralNetwork *nn)
{
    FILE *save = fopen("weights", "w");
    for (unsigned int i = 0; i < NB_HIDDEN; i++)
    {
        fprintf(save, "%f\n", nn->hidden[i]->value);
        fprintf(save, "%f\n", nn->hidden[i]->bias);
        for (unsigned int j = 0; j < nn->hidden[i]->nb_input; j++)
        {
            fprintf(save, "%f\n", nn->hidden[i]->inputweights[j]);
        }
    }
    for (unsigned int i = 0; i < NB_OUTPUT; i++)
    {
        fprintf(save, "%f\n", nn->output[i]->value);
        fprintf(save, "%f\n", nn->output[i]->bias);
        for (unsigned int j = 0; j < nn->output[i]->nb_input; j++)
        {
            fprintf(save, "%f\n", nn->output[i]->inputweights[j]);
        }
    }
    fclose(save);
}

/*
 * Load all weights saved in a file 'weights' (if exists) to the neural network.
 * Throw an error if the 'weights' file is invalid.
 */
void load_weights(NeuralNetwork *nn)
{
    FILE *data = fopen("weights", "r");
    if (data != NULL)
    {
        char *line = NULL;
        size_t len;

        for (unsigned int i = 0; i < NB_HIDDEN; i++)
        {
            if (getline(&line, &len, data) == -1)
                errx(1, "Invalid weights file");
            nn->hidden[i]->value = strtod(line, NULL);
            if (getline(&line, &len, data) == -1)
                errx(1, "Invalid weights file");
            nn->hidden[i]->bias = strtod(line, NULL);
            for (unsigned int j = 0; j < nn->hidden[i]->nb_input; j++)
            {
                if (getline(&line, &len, data) == -1)
                    errx(1, "Invalid weights file");
                nn->hidden[i]->inputweights[j] = strtod(line, NULL);
            }
        }
        for (unsigned int i = 0; i < NB_OUTPUT; i++)
        {
            if (getline(&line, &len, data) == -1)
                errx(1, "Invalid weights file");
            nn->output[i]->value = strtod(line, NULL);
            if (getline(&line, &len, data) == -1)
                errx(1, "Invalid weights file");
            nn->output[i]->bias = strtod(line, NULL);
            for (unsigned int j = 0; j < nn->output[i]->nb_input; j++)
            {
                if (getline(&line, &len, data) == -1)
                    errx(1, "Invalid weights file");
                nn->output[i]->inputweights[j] = strtod(line, NULL);
            }
        }
        if (getline(&line, &len, data) != -1)
            errx(1, "Invalid weights file");
        free(line);
        fclose(data);
    }
}
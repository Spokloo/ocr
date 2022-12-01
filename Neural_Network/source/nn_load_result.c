#include "nn_load_result.h"
#include "nn_tools.h"
#include <stdio.h>
#include <stdlib.h>

char **load_result(Image **im, NeuralNetwork *nn)
{
    int ind = 0;
    char **res = malloc(9 * sizeof(char *));
    for (int i = 0; i < 9; i++)
    {
        res[i] = malloc(9 * sizeof(char));
        for (int j = 0; j < 9; j++)
        {
            res[i][j] = get_output(nn, image_to_int(im[ind]), 0);
            ind++;
        }
    }
    return res;
}

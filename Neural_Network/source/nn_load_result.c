#include "nn_load_result.h"
#include "nn_tools.h"
#include <stdio.h>
#include <stdlib.h>

int **load_result(Image **im, NeuralNetwork *nn)
{
    int ind = 0;
    int **res = malloc(9 * sizeof(int *));
    char *tmp;
    for (int i = 0; i < 9; i++)
    {
        res[i] = malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++)
        {
            tmp = image_to_int(im[ind]);
            res[i][j] = get_output(nn, tmp, 0);
            free(tmp);
            ind++;
        }
    }
    return res;
}

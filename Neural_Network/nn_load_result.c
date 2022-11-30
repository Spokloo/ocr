#include <stdio.h>
#include <stdlib.h>
#include "nn_tools.h"
#include "../Tools/image.h"


char ** load_result(Image **im,NeuralNetwork *nn)
{
    int ind=0;
    char ** res = malloc(9*sizeof(char **));
    for (int i=0;i<9;i++)
    {
        char * tmp=malloc(9*sizeof(char));
        for (int j=0;j<9;j++)
        {
            tmp[j]=get_output(nn,im_to_int(im[ind]));
            ind++;
        }
        res[i]=tmp;
    }
    return res;
}

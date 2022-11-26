#include "xor.h"
#include <stdio.h>
#include <stdlib.h>
#include "adapt_softmax.h"

Neuralnetwork newxor()
{
    NeuralNetwork nn;
    // input layer

    for (int i=0;i<NB_INPUT;i++)
    {
        unit *u= malloc(sizeof(unit));
        *u=(unit){0,0,0,NULL,NULL};
        nn->input[i]= u;
    }
    for (int j=0;j<NB_HIDDEN;j++)
    {
        unit **input_l_h = malloc(2 * sizeof(unit *));
        double *input_w_h = malloc(2 * sizeof(double))
        for (int k=0;k<NB_INPUT;k++)
        {
            input_l_h[k]=nn->input[k];
            input_w_h[k]=0;
        }
        nn->hidden[j]=(unit){0,0,NB_INPUT,input_l_h,input_w_h};
    }
    for (int k=0:k<NB_OUTPUT;k++)
    {
        unit **inputz= malloc(NB_HIDDEN*sizeof(unit *))
        double *input_w_z = malloc(3 * sizeof(double));
 
        for (int j=0;j<NB_HIDDEN;j++)
        {
            inputz[j]=nn->hidden[j];
            input_w_z[j]=0    
        }
        nn->output[k]=(unit){0, 0, NB_HIDDEN, inputz, input_w_z};
        return nn;
    }
}

void free_nn(NeuralNetwork nn)
{
    for (int i=0;i<NB_INPUT;i++)
    {
        free(nn.input[i]);
    } 
    for (int j=0;j<NB_HIDDEN;j++)
    {
        free(nn.hidden[j]->inputlinks);
        free(nn.hidden[j]->inputweights);
        free(nn.hidden[j]);
    }
    for(int k=0;k<NB_OUTPUT;k++)
    {
        free(nn.output[k]->inputlinks);
        free(nn.output[k]->inputweights);
        free(nn.output[k]);
    }
}
    

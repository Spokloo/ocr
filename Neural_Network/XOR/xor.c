#include "xor.h"
#include "xor_tools.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    NeuralNetwork xor = new_xor();
    // load_weights(xor);
    double dk = 1, val = 0, diff = 1, expected;
    double precision = 0.01;
    char input[8] = {0, 0, 0, 1, 1, 0, 1, 1};
    while (((diff > 0 && diff > precision) || (diff < 0 && diff < -precision)))
    {
        diff = 0;
        for (unsigned char nb = 0; nb < 8; nb += 2)
        {
            // Give example
            xor.input[0]->value = input[nb];
            xor.input[1]->value = input[nb + 1];

            // Update activate value of hidden and output layer
            for (unsigned char i = 0; i < NB_HIDDEN; i++)
                update_activate_value(xor.hidden[i]);
            for (unsigned char i = 0; i < NB_OUTPUT; i++)
                update_activate_value(xor.output[i]);
            expected =
                calculate_expected(xor.input[0]->value, xor.input[1]->value);
            diff += fabs(expected - xor.output[0]->value);
            printf("%.f and %.f -> %f (%.f)\n", xor.input[0]->value,
                   xor.input[1]->value, xor.output[0]->value, expected);

            // Compute error between example and output
            val = xor.output[0]->value;
            dk = (expected - val) * val * (1.0 - val);

            // Update weights of links to output
            for (unsigned char i = 0; i < xor.output[0]->nb_input; i++)
                xor.output[0]->inputweights[i] +=
                    LEARNRATE *dk * xor.output[0]->inputlinks[i]->value;
            xor.output[0]->bias += LEARNRATE *dk; // *1

            // Compute error in hidden layer
            val = xor.hidden[0]->value;
            dk = val * (1.0 - val) * dk * xor.output[0]->inputweights[1];

            // Update weights of links to hidden
            for (unsigned char i = 0; i < xor.hidden[0]->nb_input; i++)
                xor.hidden[0]->inputweights[i] +=
                    LEARNRATE *dk * xor.hidden[0]->inputlinks[i]->value;
            xor.hidden[0]->bias += LEARNRATE *dk;
        }
        diff /= 4;
    }
    printf("= = = = = = = = = =\n");
    printf("Final result :\n");
    for (int i = 0; i < 8; i += 2)
    {
        xor.input[0]->value = input[i];
        xor.input[1]->value = input[i + 1];
        update_activate_value(xor.hidden[0]);
        update_activate_value(xor.output[0]);
        expected = calculate_expected(xor.input[0]->value, xor.input[1]->value);
        printf("%.f and %.f -> %f (%.f)\n", xor.input[0]->value,
               xor.input[1]->value, xor.output[0]->value, expected);
    }

    // print_xor(xor);
    // save_weights(xor);
    free_xor(xor);
    return 0;
}

void update_activate_value(unit *u)
{
    double res = 0;
    for (unsigned char i = 0; i < u->nb_input; i++)
        res += u->inputlinks[i]->value * u->inputweights[i];
    res += u->bias;
    u->value = 1.0 / (1.0 + exp(-res));
}

double calculate_expected(int i1, int i2)
{
    double sum = i1 + i2;
    double res = 0;
    if (sum == 1)
        res = 1;
    return res;
}
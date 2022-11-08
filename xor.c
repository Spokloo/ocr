#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define LEARNRATE 2 
#define NB_INPUT 2
#define NB_HIDDEN 1
#define NB_OUTPUT 1

typedef struct unit
{
    double value;
    double bias;
    unsigned char nb_input;
    struct unit **inputlinks;
    double *inputweights;
} unit;

typedef struct nn
{
    unit *input[NB_INPUT];
    unit *hidden[NB_HIDDEN];
    unit *output[NB_OUTPUT];
} nn;

nn new_xor()
{
    // input layer
    unit *x = malloc(sizeof(unit));
    *x = (unit){1, 0, 0, NULL, NULL};
    unit *y = malloc(sizeof(unit));
    *y = (unit){0, 0, 0, NULL, NULL};

    // hidden layer
    unit **input_l_h = malloc(2 * sizeof(unit *));
    input_l_h[0] = x;
    input_l_h[1] = y;
    double *input_w_h = malloc(2 * sizeof(double));
    input_w_h[0] = ((double)rand() / RAND_MAX * 2) - 1;
    input_w_h[1] = ((double)rand() / RAND_MAX * 2) - 1;
    unit *h = malloc(sizeof(unit));
    *h = (unit){0.5, ((double)rand() / RAND_MAX * 2) - 1, 2, input_l_h, input_w_h};

    // output layer
    unit **inputz = malloc(3 * sizeof(unit *));
    inputz[0] = x;
    inputz[1] = h;
    inputz[2] = y;
    double *input_w_z = malloc(3 * sizeof(double));
    input_w_z[0] = ((double)rand() / RAND_MAX * 2) - 1;
    input_w_z[1] = ((double)rand() / RAND_MAX * 2) - 1;
    input_w_z[2] = ((double)rand() / RAND_MAX * 2) - 1;
    unit *z = malloc(sizeof(unit));
    *z = (unit){0.5, ((double)rand() / RAND_MAX * 2) - 1, 3, inputz, input_w_z};

    nn xor = {{x, y}, {h}, {z}};
    return xor;
}

void free_xor(nn xor)
{
    free(xor.input[0]);
    free(xor.input[1]);
    free(xor.hidden[0]->inputlinks);
    free(xor.hidden[0]->inputweights);
    free(xor.hidden[0]);
    free(xor.output[0]->inputlinks);
    free(xor.output[0]->inputweights);
    free(xor.output[0]);
}

void update_activate_value(unit *u)
{
    double res = 0;
    for (unsigned char i = 0; i < u->nb_input; i++)
    {
        // printf("%f * %f + ", u->inputlinks[i]->value, u->inputweights[i]);
        res += u->inputlinks[i]->value * u->inputweights[i];
    }
    // printf("\nres : %f\n", res);
    u->value = 1.0 / (1.0 + exp(-(res + u->bias)));
}

void generate_input(char input[NB_INPUT])
{
    for (unsigned char i = 0; i < NB_INPUT; i++)
    {
        input[i] = rand() % 2;
    }
}

double calculate_expected(int i1, int i2)
{
    double sum = i1 + i2;
    double res = 0;
    if (sum == 1)
        res = 1;
    return res;
}

void print_unit(unit *n)
{
    printf("value : %f\n", n->value);
    printf("bias : %f\n", n->bias);
    printf("nbinput : %d\n", n->nb_input);
    for (int i = 0; i < n->nb_input; i++)
        printf("value : %f and weight : %f\n", n->inputlinks[i]->value, n->inputweights[i]);
}
void print_xor(nn xor)
{
    printf("z : \n");
    print_unit(xor.output[0]);
    printf("h : \n");
    print_unit(xor.hidden[0]);
    printf("x : \n");
    print_unit(xor.input[0]);
    printf("y : \n");
    print_unit(xor.input[1]);
}

int main()
{
    nn xor = new_xor();
    // print_xor(xor);
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
            expected = calculate_expected(xor.input[0]->value, 
                                                        xor.input[1]->value);
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

    free_xor(xor);
    return 0;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LR 0.25
#define NB_INPUT 2
#define NB_HIDDEN 2
#define NB_OUT 1

typedef struct neural_first_layer
{
    int value;
    double weights[NB_HIDDEN];
    double weight_out;
} neural_first_layer;

typedef struct neural_second_layer
{
    double value;
    double weights[NB_OUT];
    double bias;
} neural_second_layer;

double generate_weigth(int nb_next)
{
    double max = 2.4 / nb_next;
    double min = -2.4 / nb_next;
    double a = (double)RAND_MAX;
    double div = a / (max - min);
    int random = rand();
    return min + (random / div);
};

typedef struct out
{
    struct neural_second_layer second_layer[2];
    double value;
    double bias;
    double gradient;
} out;

void init_all(neural_first_layer layer1[NB_INPUT],
              neural_second_layer layer2[NB_HIDDEN], out *o1)
{
    for (int i = 0; i < NB_INPUT; i++)
    {
        for (int k = 0; k < NB_HIDDEN; k++)
        {
            layer1[i].weights[k] = generate_weigth(NB_HIDDEN);
        }
        layer1[i].weight_out = generate_weigth(NB_OUT);
    }

    for (int j = 0; j < NB_HIDDEN; j++)
    {
        for (int k = 0; k < NB_OUT; k++)
        {
            layer2[j].weights[k] = generate_weigth(NB_OUT);
        }
        layer2[j].bias = generate_weigth(NB_OUT);
    }
    o1->bias = generate_weigth(NB_OUT);
}

void activation_hidden(neural_second_layer layer[NB_HIDDEN])
{
    for (int j = 0; j < NB_HIDDEN; j++)
    {
        layer[j].value = 1 / (1 + exp(-layer[j].value));
    }
}

void gradient_out(out *out_n, neural_second_layer layer[NB_HIDDEN],
                  neural_first_layer layer2[NB_INPUT], double gradient)
{
    for (int i = 0; i < NB_HIDDEN; i++)
    {
        layer[i].weights[0] += LR * (*out_n).value * gradient;
    }
    out_n->bias += LR * -1 * gradient;
}

void calculate_error_gradient_out(out *o, double e)
{
    o->gradient = o->value * (1 - o->value) * e;
}

double calculate_error_gradient_hidden(double output, double weight,
                                       double gradient)
{
    double res = output * (1 - output) * gradient * weight;

    return res;
}

void generate(int *a)
{
    int n1 = rand() % 2;
    int n2 = rand() % 2;
    a[0] = n1;
    a[1] = n2;
}

double sum_first(int j, neural_second_layer *neural,
                 neural_first_layer n1[NB_INPUT])
{
    double sum = 0;

    for (int i = 0; i < NB_INPUT; i++)
    {
        sum += n1[i].value * n1[i].weights[j];
    }
    return sum;
}

void init_(neural_first_layer l1[NB_INPUT], neural_second_layer l2[NB_HIDDEN],
           out *o)
{
    l1[0].weights[0] = 0.50;
    l1[0].weights[1] = 0.90;
    l1[1].weights[0] = 0.40;
    l1[1].weights[1] = 1.0;
    l2[0].weights[0] = -1.0;
    l2[1].weights[0] = 1.10;
    l2[0].bias = 0.80;
    l2[1].bias = -0.10;
    o->bias = 0.30;
}

double sum_out(out *o, neural_second_layer second_layer[NB_HIDDEN],
               neural_first_layer l1[NB_INPUT])
{
    double sum = 0;
    for (int i = 0; i < NB_HIDDEN; i++)
        sum += second_layer[i].value * second_layer[i].weights[0];
    return sum;
}

void change_out_weigth_apply(out *out, double g,
                             neural_first_layer l1[NB_INPUT],
                             neural_second_layer l2[NB_HIDDEN])
{
    out->gradient = g;
    gradient_out(out, l2, l1, g);
}

void change_hidden_weigth_apply(neural_first_layer l1[NB_INPUT],
                                neural_second_layer l2[NB_HIDDEN], out *out)
{
    for (int k = 0; k < NB_HIDDEN; k++)
    {

        double g = calculate_error_gradient_hidden(out->value, l2[k].weights[0],
                                                   out->gradient);

        for (int j = 0; j < NB_INPUT; j++)
        {
            l1[j].weights[k] += LR * l1[j].value * g;
        }
        l2[k].bias += LR * -1 * g;
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
void print_weights(neural_first_layer l1[NB_INPUT],
                   neural_second_layer l2[NB_HIDDEN], out o1)
{
    for (int i = 0; i < NB_INPUT; i++)
    {
        for (int j = 0; j < NB_HIDDEN; j++)
            printf("%f  ", l1[i].weights[j]);
    }
    printf("\n");
    for (int i = 0; i < NB_HIDDEN; i++)
    {
        for (int j = 0; j < NB_OUT; j++)
            printf("%f  ", l2[i].weights[j]);
        printf("%f------", l2[i].bias);
    }
    printf("\n\n");
}

int main()
{
    struct neural_first_layer l1[NB_INPUT];

    for (int i = 0; i < NB_INPUT; i++)
    {
        for (int j = 0; j < NB_HIDDEN; j++)
            l1[i].weights[j] = 0;
        l1[i].value = 0;
        l1[i].weight_out = 0;
    }
    struct neural_second_layer l2[3];
    struct out o1;
    int w = 0;
    for (int i = 0; i < NB_HIDDEN; i++)
    {
        for (int k = 0; k < NB_OUT; k++)
        {
            l2[i].weights[k] = 0;
        }
        l2[i].bias = 0;
        l2[i].value = 0;
    }
    o1.bias = 0;
    init_(l1, l2, &o1);
    int arr_input[NB_INPUT];
    for (int i = 0; i < NB_INPUT; i++)
    {
        arr_input[i] = 0;
    }
    int sample[8] = {0, 0, 1, 0, 0, 1, 1, 1};
    double e = 1;
    double expected;
    double seuil = 0.001;
    while ((e > seuil && e > 0) || (e < -seuil && e < 0))
    {
        // arr_input[0]=1;
        // arr_input[1]=1;
        arr_input[0] = sample[(w % 4) * 2];
        arr_input[1] = sample[(w % 4) * 2 + 1];
        for (int k = 0; k < NB_INPUT; k++)
        {
            l1[k].value = arr_input[k];
        }
        for (int i = 0; i < NB_HIDDEN; i++)
        {
            neural_second_layer *np = &l2[i];
            np->value = 1 / (1 + exp(-(sum_first(i, np, l1) - np->bias)));
        }
        double sum = sum_out(&o1, l2, l1);
        o1.value = 1 / (1 + exp(-(sum - o1.bias)));
        expected = calculate_expected(l1[0].value, l1[1].value);
        e = expected - o1.value;
        printf("in : %d  %d expected %f  got %f \n", l1[0].value, l1[1].value,
               expected, o1.value);
        // printf("%f\n",l1[0].weights[0]);
        // print_weights(l1,l2,o1);
        calculate_error_gradient_out(&o1, e);
        change_out_weigth_apply(&o1, o1.gradient, l1, l2);
        change_hidden_weigth_apply(l1, l2, &o1);
        w++;
    }
    return 0;
}

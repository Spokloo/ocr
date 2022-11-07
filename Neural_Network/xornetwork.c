#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LR 0.1
#define NB_INPUT 2
#define NB_HIDDEN 2 
#define NB_OUT 1

typedef struct neural_first_layer
{
    int value;
    double weights[NB_HIDDEN];
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

void init_all(neural_first_layer layer1[NB_INPUT], neural_second_layer layer2[NB_HIDDEN], out *o1)
{
    for (int i = 0; i < NB_INPUT; i++)
    {
        for (int k = 0; k < NB_HIDDEN; k++)
        {
            layer1[i].weights[k] = generate_weigth(NB_HIDDEN);
        }
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
    double sum=0;
    for (int k=0;k<NB_HIDDEN;k++)
    {
        sum+=exp(layer[k].value);
    }
    for (int j=0;j<NB_HIDDEN;j++)
    {
        layer[j].value= exp(layer[j].value)/sum;
    }
}

void gradient_out(out *out_n, neural_second_layer layer[NB_HIDDEN], double gradient, double lr)
{
    for (int i = 0; i < NB_HIDDEN; i++)
    {
        layer[i].weights[0] += lr * (*out_n).value * gradient;
    }
    out_n->bias += lr * -1 * gradient;
}

void calculate_error_gradient_out(out *o, double e)
{
    o->gradient = o->value * (1 - o->value) * e;
}

double calculate_error_gradient_hidden(double output, double weight, double gradient)
{
    return output * (1 - output) * gradient * weight;
}

double new_weigth(double lr, double value, double gradient)
{
    return lr * value * gradient;
}

void generate(int *a)
{
    int n1 = rand() % 2;
    int n2 = rand() % 2;
    a[0] = n1;
    a[1] = n2;
}

double sum_first(neural_second_layer *neural, neural_first_layer n1[NB_INPUT])
{
    double sum = 0;
    for (int j = 0; j < NB_HIDDEN; j++)
    {
        for (int i = 0; i < NB_INPUT; i++)
        {
            sum += n1[i].value * n1[i].weights[j];
        }
    }
    return sum + neural->bias;
}

double sum_out(out *o, neural_second_layer second_layer[NB_HIDDEN])
{
    double sum = 0;
    for (unsigned long int i = 0; i < NB_HIDDEN; i++)
        sum += second_layer[i].value * second_layer[i].weights[0];

    return sum;
}

void change_out_weigth_apply(out *out, double g, neural_second_layer l2[NB_HIDDEN])
{
    out->gradient = g;
    gradient_out(out, l2, g, 0.1);
}

void change_hidden_weigth_apply(neural_first_layer l1[NB_INPUT], neural_second_layer l2[NB_HIDDEN], out *out)
{
    for (int k = 0; k < NB_HIDDEN; k++)
    {

        double g = calculate_error_gradient_hidden(out->value, l2[k].weights[k], out->gradient);

        for (int j = 0; j < NB_INPUT; j++)
        {

            l1[j].weights[k] += LR * l1[j].value * g;
        }
        l2[k].bias += -1*LR * g;
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

int main()
{
    struct neural_first_layer l1[NB_INPUT];

    for (int i = 0; i < NB_INPUT; i++)
    {
        for (int j = 0; j<NB_HIDDEN; j++)
            l1[i].weights[j] = 0;
        l1[i].value = 0;
    }
    struct neural_second_layer l2[NB_HIDDEN];
    struct out o1;
    int w=0;
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
    init_all(l1, l2, &o1);
    int arr_input[NB_INPUT];
    for(int i = 0; i < NB_INPUT; i++)
    {
        arr_input[i] = 0;
    }
    double e = 1;
    double expected;
    double seuil = 0.001;
    while (w<1000 && ((e > seuil && e > 0) || (e < -seuil && e < 0)))
    {
        //generate(arr_input);
        for (int k = 0; k < NB_INPUT; k++)
        {
            l1[k].value = arr_input[k];
        }
        for (int i = 0; i < NB_HIDDEN; i++)
        {
            l2[i].value = sum_first(&l2[i], l1);
        }
        activation_hidden(l2);
        double sum=sum_out(&o1, l2);
        o1.value= 1/(1+exp(-sum));
        expected = calculate_expected(arr_input[0], arr_input[1]);
        e = expected - o1.value;
        printf("in : %d  %d expected %f  got %f \n", l1[0].value, l1[1].value, expected, o1.value);
        //printf("%f\n",l2[0].weights[0]);
        calculate_error_gradient_out(&o1, e);

        change_out_weigth_apply(&o1, o1.gradient, l2);
        change_hidden_weigth_apply(l1, l2, &o1);
        w++;
    }
    return 0;
}

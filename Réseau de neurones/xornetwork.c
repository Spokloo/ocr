#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LR 0.1
#define NB_INPUT 2
#define NB_HIDDEN 2
#define NB_OUT 1
double w11 = 0.22;
double w12 = -0.45;
double w21 = 0.15;
double w22 = 0.35;
int val_bias=-1;
double bias_21=0.8;
double bias_22=-0.1;
double bias_31=0.3;
double biais_out[]= {0.5};
double learnrate = 0.1;


struct neural_first_layer
{
    int value;
    double weights[2];
}input1,input2;

struct neural_first_layer *i1=&input1;

struct neural_first_layer *i2=&input2;
struct neural_first_layer layer1[2];


void init_weigth(){
    i1->weights[0]=w11;
    i1->weights[1]=w12;
    i2->weights[0]=w21;
    i2->weights[1]=w22;
    layer1[0]=*i1;
    layer1[1]=*i2;
}


struct neural_second_layer
{
    double value;
    struct neural_first_layer previous[2];
    double weights[NB_OUT];
    double bias;
}n1,n2;


struct neural_second_layer layer2[2];


void init_second()
{
    n1.weights[0]=w21;
    n2.weights[0]=w22;
    n1.bias=bias_21;
    n2.bias=bias_22;
    layer2[0]=n1;
    layer2[1]=n2;
}

struct out
{
    struct neural_second_layer second_layer[2];
    double value;
    double bias;
    double gradient;
}o1;
void init_out()
{
    o1.bias=bias_31;
}
double activation(float value){
    return 1/(1 + exp(-value));
}


double calculate_delta(double expected,double output){
    return (expected-output)*output*(1-output);
}

double change_weight_out(double d, double learnrate, double out){
    return d*learnrate*out;
}
void gradient_out(struct out out_n, double gradient, double lr){
    for (int i;i<2;i++){
        out_n.second_layer[i].bias= lr*-1*gradient;  
        out_n.second_layer[i].weights[0] += lr*out_n.value*gradient;
    }
}

double calculate_error_gradient_out(double output,double e){
    return output*(1-output)*e;
}

double calculate_error_gradient_hidden(double output, double weight, double gradient){
    return output*(1-output)*gradient*weight;
}

double new_weigth(double lr, double value,double gradient){
    return lr*value*gradient;
}


void generate(int *a)
{
    int n1= rand()%2;
    int n2= rand()%2;
    a[0]=n1;
    a[1]=n2;
}

void sum_first(struct neural_second_layer neural)
{
    double sum=0;
    for (int j=0;j<NB_HIDDEN;j++)
    {
        for (int i=0; i<NB_INPUT;i++){
            sum+=neural.previous[j].value*neural.previous[j].weights[i];
        }
    }
    neural.value= activation(sum+neural.bias);
    
}

void sum_out(struct out neural)
{
    float sum=0;
    for (unsigned long int i=0; i<NB_HIDDEN;i++)
        sum+=neural.second_layer[i].value * neural.second_layer->weights[i];
    
    neural.value= activation(sum+neural.bias);
   
}



void change_out_weigth_apply(double expected, struct out out, double g)
{
    out.gradient=g;
    gradient_out(out,g,0.1); 
}

void change_hidden_weigth_apply(struct neural_second_layer *l, struct out out)
{
    for (int k=0;k<NB_HIDDEN;k++)
    {
   
        double g=calculate_error_gradient_hidden(l[k].value,l[k].weights[0],out.gradient);
        
        for (int j=0;j<NB_INPUT;j++)
        {
            l[k].previous[j].weights[j]+=LR*l[k].previous[j].value*g; 
        }
        l[k].bias+=LR*(-1)*g;
    }
}

double calculate_expected(int i1,int i2)
{
    double sum=i1+i2;
    double res=0;
    if (sum==1) 
        res=1;
    return res;
}


int main(){
    init_weigth();
    init_second();
    init_out();
    int arr_input[2];
    double e=1;
    
    double seuil=0.001;
    while (e>seuil)
    {
       
        generate(arr_input);
      
        for (int k=0;k<NB_INPUT;k++)
        {
            layer1[k].value=arr_input[k];
        }
        for (int i=0;i<NB_HIDDEN;i++)
        {
            sum_first(layer2[i]);
        }
        sum_out(o1);
        e = calculate_expected(arr_input[0],arr_input[1])-o1.value;
        double g=calculate_error_gradient_out(o1.value,e);
        change_out_weigth_apply(e,o1,g);
        change_hidden_weigth_apply(layer2,out); 
    }
    return 0;
}


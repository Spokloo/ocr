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
struct neural_first_layer layer1[NB_INPUT];


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


void gradient_out(struct out out_n, struct neural_second_layer second_layer[NB_HIDDEN],double gradient, double lr){
    for (int i=0;i<NB_HIDDEN;i++){
        layer2[i].weights[0] += lr*out_n.value*gradient;
    }

    o1.bias += lr*1*gradient;  
}

void calculate_error_gradient_out(double output,double e){
    o1.gradient= output*(1-output)*e;
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

double sum_first(struct neural_second_layer neural, struct neural_first_layer n1[2])
{
    double sum=0;
    for (int j=0;j<NB_HIDDEN;j++)
    {
        for (int i=0; i<NB_INPUT;i++){
            sum+=n1[i].value*n1[i].weights[j];
        }
    }
    return sum+neural.bias;
    
}

void sum_out(struct out neural, struct neural_second_layer second_layer[NB_HIDDEN])
{
    float sum = 0;
    for (unsigned long int i=0; i<NB_HIDDEN;i++)
        sum+=second_layer[i].value * second_layer[i].weights[i];
     
    o1.value = activation(sum+neural.bias);
}



void change_out_weigth_apply(struct neural_second_layer l2[NB_HIDDEN],struct out out, double g)
{
    out.gradient=g;
    gradient_out(out,l2,g,0.1); 
}

void change_hidden_weigth_apply(struct neural_first_layer n1[NB_INPUT],struct neural_second_layer *l, struct out out)
{
    for (int k=0;k<NB_HIDDEN;k++)
    {
   
        double g=calculate_error_gradient_hidden(o1.value,l[k].weights[k],out.gradient);
        
        for (int j=0;j<NB_INPUT;j++)
        {
            
            layer1[j].weights[k]+=LR*layer1[j].value*g;
            
        }
        layer2[k].bias+=LR*(1)*g;
   
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
    arr_input[0]=0;
    arr_input[1]=0;
    double e=1;
    double expected;
    double seuil=0.001;
    while ((e>seuil && e>0) || (e<-seuil && e<0))
    {
        for (int k=0;k<NB_INPUT;k++)
        {
            layer1[k].value=arr_input[k];
        }
        for (int i=0;i<NB_HIDDEN;i++)
        {
            layer2[i].value=sum_first(layer2[i],layer1);
        }
        //printf("%f %f\n",layer2[0].value, layer2[0].bias);
     
        sum_out(o1, layer2);
        //printf("%f   ",o1.value);
        expected=calculate_expected(arr_input[0],arr_input[1]);
        e = expected-o1.value;
        printf("in : %d  %d expected %f  got %f \n",layer1[0].value,layer1[1].value,expected,o1.value);
        
        calculate_error_gradient_out(o1.value,e);
    
        change_out_weigth_apply(layer2,o1,o1.gradient);
        change_hidden_weigth_apply(layer1,layer2,o1); 
    }
    return 0;
}


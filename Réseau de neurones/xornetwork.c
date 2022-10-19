#include <math.h>
#include <stdio.h>



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
    double weights[2];
    double bias;
}n1,n2;


struct neural_second_layer layer2[2];


void init_second(){
    layer2[0]=n1;
    layer2[1]=n2;
}

struct out
{
    struct neural_second_layer second_layer[2];
    double weights[2];
    double value;
    double bias;
}o1;

double activation(float value){
    return 1/(1+exp(-value));
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


double *generate()
{
    int n1= rand()%2;
    int n2= rand()%2;
    double res1=(double)n1;
    double res2=(double)n2;
    double arr[2];
    arr[0]=res1;
    arr[1]=res2;
    return arr;
}

void sum_first(struct neural_second_layer neural)
{
    double sum=0;
    for (long unsigned int j=0;j<sizeof(neural.previous[j])/sizeof(struct neural_first_layer);j++)
    {
        for (long unsigned int i=0; i<sizeof(neural.previous[i].weights)/sizeof(double);i++){
            sum+=neural.previous[j].value*neural.previous[j].weights[i];
        }
    }
    neural.value= activation(sum+neural.bias);
    
}

float sum_out(struct out neural, int i)
{
    float sum=0;
    for (long unsigned int j=0;j<sizeof(neural.second_layer)/sizeof(struct neural_second_layer);j++)
    {
        for (unsigned long int i=0; i<sizeof(neural.second_layer[j])/sizeof(double);i++)

        sum+=neural.second_layer[j].value * neural.weights[i];
    }
    neural.value= activation(sum+neural.bias);
   
}

void change_out_weigth_apply(double expected, struct out out)
{
    double g=calculate_error_gradient_out(out.value,expected-out.value);
    gradient_out(out,g,0.1); 
}





main(){
    

}


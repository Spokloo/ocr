#include <math.h>
#include <stdio.h>



float w11 = 0.22;
float w12 = -0.45;
float w21 = 0.15;
float w22 = 0.35;
const val_bias=-1;
float bias_21=0.8;
float bias_22=-0.1;
float bias_31=0.3;
float bias[]= {bias21,bias22,bias31};
float biais_out[]= {0.5};
float learnrate = 0.1;


struct neural_first_layer
{
    int value;
    float weights[2];
}input1,input2

input1.weights[0]=w11;
input1.weights[1]=w12;
input2.weights[0]=w21;
input2.weights[1]=w22;

neural_first_layer layer1[2]={input1,input2};


struct neural_second_layer
{
    float value;
    neural_first_layer previous[2];
    float weigth[2];
    float bias;
}n1,n2



neural_second_layer layer2={n1,n2};


struct out
{
    neural_second_layer second_layer[2];
    float weight;
}

double activation(float value){
    return 1/(1+exp(-value));
}


double calculate_delta(double expected,double output){
    return (expected-output)*output*(1-output);
}

void change_weight_out(double weight, double learnrate, double out){
    weigth += weight*learnrate*out;
}
double calculate_error_gradient_hidden(double output,double e,double weigth){
    return output*(1-output)*e*weigth;
}


void sum_first(neural_second_layer neural, int i)
{
    float sum=0;
    for (int j=0;neural.previous[j]!=EOF;j++)
    {
        sum+=neural.previous[j].value*weigth[i];
    }
    neural.value= activation(sum+neural.bias);
    
}

float sum_out(out neural, int i)
{
    float sum=0;
    for (int j=0;neural.second_layer[j]!=EOF;j++)
    {
        sum+=neural.second_layer[j].value*weigth[i];
    }
    return sum+neural.bias;
    
}


main(){
    

}


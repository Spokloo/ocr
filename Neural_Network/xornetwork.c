#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LR 0.1
#define NB_INPUT 2
#define NB_HIDDEN 2
#define NB_OUT 1
double learnrate = 0.1;


struct neural_first_layer
{
    int value;
    double weights[NB_HIDDEN];
}i1,i2;





struct neural_second_layer
{
    double value;
    double weights[NB_OUT];
    double bias;
}n1,n2;


double generate_weigth(int nb_next)
{
    double max = 2.4/nb_next;
    double min = -2.4/nb_next;
    double a= (double) RAND_MAX;
    double div = a/(max-min);
    int random =rand();
    return min+(random/div);
};


struct out
{
    struct neural_second_layer second_layer[2];
    double value;
    double bias;
    double gradient;
}o1;


void init_all(struct neural_first_layer **layer1, struct neural_second_layer **layer2, struct out *o1)
{
    for (int i=0;i<NB_INPUT;i++)
    {
        for (int k=0;k<NB_HIDDEN;k++)
        {
            layer1[i]->weights[k]=generate_weigth(NB_HIDDEN);
        }
    }
   
    for (int j=0;j<NB_HIDDEN;j++)
    {
        for (int k=0;k<NB_OUT;k++)
        {
            layer2[j]->weights[k]=generate_weigth(NB_OUT);
        }
        layer2[j]->bias=generate_weigth(NB_OUT);

    } 
    o1->bias=generate_weigth(NB_OUT);    
}


double activation(float value){
    return 1/(1 + exp(-value));
}


void gradient_out(struct out *out_n, struct neural_second_layer **layer, double gradient, double lr){
    for (int i=0;i<NB_HIDDEN;i++){
        layer[i]->weights[0] += lr*(*out_n).value*gradient;
    }
    out_n->bias += lr*1*gradient;
  
}

void calculate_error_gradient_out(struct out *o,double e){
    o->gradient= o->value*(1-o->value)*e;
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

double sum_first(struct neural_second_layer *neural, struct neural_first_layer *n1[2])
{
    double sum=0;
    for (int j=0;j<NB_HIDDEN;j++)
    {
        for (int i=0; i<NB_INPUT;i++){
            sum+=n1[i]->value*n1[i]->weights[j];
        }
    }
    return sum+neural->bias;
    
}

void sum_out(struct out *o,struct neural_second_layer *second_layer)
{
    double sum = 0;
    for (unsigned long int i=0; i<NB_HIDDEN;i++)
        sum+=second_layer[i].value * second_layer[i].weights[i];
     
    o->value = activation(sum+o->bias);
}



void change_out_weigth_apply(struct out *out, double g, struct  neural_second_layer *l2)
{
    out->gradient=g;
    gradient_out(out,&l2,g,0.1); 
}

void change_hidden_weigth_apply(struct neural_first_layer **l1,struct neural_second_layer **l2, struct out *out)
{
    for (int k=0;k<NB_HIDDEN;k++)
    {
   
        double g=calculate_error_gradient_hidden(out->value,l2[k]->weights[k],out->gradient);
        
        for (int j=0;j<NB_INPUT;j++)
        {
            
            l1[j]->weights[k]+=LR*l1[j]->value*g;
            
        }
        l2[k]->bias+=LR*(1)*g;
   
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


int main()
{ 
    struct neural_first_layer *l1= malloc(NB_INPUT*sizeof(struct neural_first_layer));
    for (int i=0;i<NB_INPUT;i++)
    {
        for (int k=0;k<NB_HIDDEN;k++)
        {
            l1[i].weights[k]=0;
        }
    }
 
    struct neural_second_layer *l2= malloc(NB_HIDDEN*sizeof(struct neural_second_layer)); 
    struct out o1;
    l2[0]=struct neural_second_layer;
    l2[1]==struct neural_second_layer;
    for (int i=0;i<NB_HIDDEN;i++)
    {
        for (int k=0;k<NB_OUT;k++)
        {
            l2[i].weights[k]=0;
        }
        l2[i].bias=0;
    } 
    o1.bias=0;
    init_all(&l1,&l2,&o1);
    int arr_input[2];

    arr_input[0]=1;
    arr_input[1]=1;
    double e=1;
    int w=0;
    double expected;
    double seuil=0.001;
    while (w<10 && (e>seuil && e>0) || (e<-seuil && e<0))
    {
        //generate(arr_input);
        for (int k=0;k<NB_INPUT;k++)
        {
            l1[k].value=arr_input[k];
        }
        for (int i=0;i<NB_HIDDEN;i++)
        {
            l2[i].value=sum_first(&l2[i],&l1);
        }
        sum_out(&o1,l2);
        expected=calculate_expected(arr_input[0],arr_input[1]);
        e = expected-o1.value;
        printf("in : %d  %d expected %f  got %f \n",l1[0].value,l1[1].value,expected,o1.value);
        //printf("%f\n",l2[0].weights[0]);
        calculate_error_gradient_out(&o1,e);
    
        change_out_weigth_apply(&o1,o1.gradient,l2);
        change_hidden_weigth_apply(&l1,&l2,&o1); 
        w++;
    }
    return 0;
}


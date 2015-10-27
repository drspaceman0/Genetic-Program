#include"indiv.h"
#include<iostream>
#include<cmath>

float inputs[10] = {0.3097535054,
                    1.1595793555,
                    -5.9924276546,
                    -2.5377665139,
                    -6.8845409271,
                    2.3317651377,
                    -2.3597796385,
                    -0.0612212234,
                    7.7767242228,
                    -2.9864402354
};

float inputs2[10] = {1.2266811919,
                    2.4671820055,
                    18.472775543,
                    5.8619010084,
                    1.7937873585,
                    8.4341642852,
                    14.8804376893,
                    16.4436206407,
                    17.9093542775,
                    9.2045037231
};

float outputs[10] = {-7.9956918867,
                    25.1971337986,
                    36.0515332303,
                    30.9331275161,
                    -59.0128364741,
                    42.2274413689,
                    52.8311153124,
                    55.1301136119,
                    45.8919589899,
                    32.4815639143
};

int NUM_ENTRIES = 10;

indiv::indiv(){
    the_indiv = new node;
    terms = 0;
    non_terms = 0;
    size = 0;
    fitness = 0;
}//indiv()

indiv::~indiv(){
    //the_indiv->erase();
}//~indiv()

/* calls a recursive function to erase/free the tree.
 */
void indiv::erase(void){
    the_indiv -> erase();
    //the_indiv = new node;
    //the_indiv = NULL;
}

void indiv::copy(indiv s){
    if(the_indiv == s.the_indiv)
        return;
    if(the_indiv != NULL)
        the_indiv->erase();
    the_indiv = new node;
    the_indiv->copy(s.the_indiv, NULL);
    size = s.size;
    fitness = s.fitness;
    terms = s.terms;
    non_terms = s.non_terms;
}

/* Generates a random full tree.*/
void indiv::generate(int max_depth){
    the_indiv = new node;
    the_indiv->full(0,max_depth,NULL);
}

/* Calculates the size of an individual's tree.*/
int indiv::calc_size(void){
    terms = 0;
    non_terms = 0;
    size = 0;
    the_indiv->calc_size(terms,non_terms);
    size = (terms + non_terms);
    return size;
}

/* Calculates fitness.
   For the symbolic regression problem it has to reevaluate the expression
   tree for each of the X points.
   The square root of the sum of the squared errors at each of those
   points is the fitness.
*/

double indiv::evaluate(void){
    fitness = 0;
    float output;
    for(int j=0; j < NUM_ENTRIES; j++){
        output = the_indiv-> evaluate(inputs[j], inputs2[j]);
        fitness += pow((output-outputs[j]), 2);
    }
    fitness = sqrt(fitness) + (calc_size() * .01);
    return fitness;
}


float indiv::return_output(void){
    ofstream myfile;
    myfile.open("/home/eric/Desktop/outputs.txts", ios::app);
    int NUM_ENTRIES = 10;
    fitness = 0;
    float output;
    for(int j=0; j < NUM_ENTRIES; j++){
        output = the_indiv-> evaluate(inputs[j], inputs2[j]);
        myfile << output <<endl;
    }
    myfile.close();
    return 1;
}


void indiv::print_indiv_tree(double X, double X2){
    the_indiv->print_function(X,X2);
    cout << endl;
    return;
}



#ifndef INDIV_H
#define INDIV_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#include"node.h"
/* Defines the indiv class.  Each individual has a fitness,
   size, number of terminals (terms), number of non-terminals,
   and a pointer to the root node of the actual tree.
   Many of the functions simply call functions in the node class.
*/

class indiv{
    private:
        int size;       // total number of nodes in the tree
        float fitness;  // fitness of the individual
        int terms;      // total number of terminals in the tree
        int non_terms;  // total number of non-terminals in the tree
    public:
        node *the_indiv;    // pointer to the root of the 'program' tree
        indiv();
        ~indiv();
        void erase(void);
        void copy(indiv);
        void generate(int);
        int calc_size(void);
        double evaluate(void);
        void print_indiv_tree(double, double);
        void evaluate_print(void);
        float return_output(void);
        float get_size(void)  {return size;}
        int get_terms(void)   {return terms;}
        int get_nonterms(void){return non_terms;}
        node* get_root(void)  {return the_indiv;}
        float get_fitness(void){return fitness;}
        void walk_terms(int &depth, node*& N){get_root()->walk_terms(depth, N);}
        void walk_nonterms(int &depth, node*& N){get_root()->walk_terms(depth, N);}
        void walk(int &depth, node*& N){get_root()->walk(depth, N);}
        void mutate(){get_root()->mutate();}
};
#endif INDIV_H

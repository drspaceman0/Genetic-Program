#ifndef NODE_H
#define NODE_H

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

typedef enum command{ add,subtract,multiply,divide, greater_than, less_than, inputX,inputX2, constt} command;

const double CONST_LIMIT = 10.0;

// non-terminals are add, subtract, multiply, divide, greater than, less than
#define NUM_NON_TERMS 6
// terminals are X and constants
#define NUM_TERMS 3
// Total ops are the sum of the previous 2
#define TOTAL_OPS 9
// max arity of any of the functions, can be changed
// unused branches point to NULL
// 4 in case you want to add conditionals
#define MAX_ARITY 2

#define MPROB 3
#define P_SIZE 100
#define GENS 500
#define MAX_DEPTH 5
#define TOURNEY 3


class node{
    public:
        node();
        ~node();
        void copy(node*, node*);  // copies trees
        void erase(void);  // recursively erases/frees trees
        void full(int,int,node *);  // generate random full trees
        void mutate();
        void trim(int); // reduce size
        double evaluate(double,double);  // calculates fitness
        void calc_size(int&,int&);  // pass by reference is for terms, non_terms
        void walk_terms(int&, node*&);
        void walk_nonterms(int&, node*&);
        void walk(int&, node*&);


        void print_function(double, double);
        void set_parent(node* p){parent = p;};
        node* get_parent(){return parent;};
        double constValue;  // stores the constant, if any
        short int type;  // stores the terminal or non-terminal
        node *parent;  // pointer to parent node
        node *branches[MAX_ARITY];  // pointers to branches
    private:

};
#endif NODE_H

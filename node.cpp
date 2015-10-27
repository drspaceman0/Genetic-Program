#include"node.h"

node::node(){
    parent = NULL;
    constValue = -1.0;
    type = -1;
    for(int i = 0; i < MAX_ARITY; i++)
        branches[i] = NULL;
}//node()

node::~node(){
    constValue = NULL;
    type = NULL;
    parent = NULL;
    for(int i = 0; i < MAX_ARITY; i++)
        branches[i] = NULL;
    //delete parent;

}//~node()

void node::copy(node *source, node* p){
    type = source->type;
    parent = p;
  /*
  if (p != NULL){
    for (int i = 0; i < MAX_ARITY; i++){
      if (p->branches[i] == source)
	p->branches[i] = this;
    }
  }
  */
    constValue = source->constValue;
    if(type < NUM_NON_TERMS){
        for(int i = 0; i < MAX_ARITY; i++){
            if(source->branches[i] != NULL){
                branches[i] = new node;
                branches[i]->copy(source->branches[i], this);
            }
            else{
                branches[i] = NULL;
            }
        }
    }
}//copy()

void node::erase(void){
    if(type < NUM_NON_TERMS){
        for(int i = 0; i < MAX_ARITY; i++){
            if(branches[i] != NULL)
                branches[i]->erase();
        }
    }
    delete this;
}//erase()

/* Generate a random tree */
void node::full(int depth,int max,node *p){
    parent = p;
    if(depth >= max) // if at max depth put in terminal
        type = NUM_NON_TERMS + rand()%NUM_TERMS;
    else{    // else add non-terminal
        type=rand()%NUM_NON_TERMS;
        switch (type){
            case add:
            case subtract:
            case multiply:
            case divide:
            case greater_than:
            case less_than:
            for(int i =0; i < MAX_ARITY; i++){
                branches[i] = new node;
                branches[i]->full(depth+1,max,this);
            }
            break;
            default:
                cout << "Unknown case in full"  << endl;
        }
    }
    if(type == constt)  // if a constant include a value
        constValue = double(drand48() * 2.0 * CONST_LIMIT) - (CONST_LIMIT/2.0);
}//full()

void node::mutate(){
    if(type >= NUM_NON_TERMS){	// count size
        if (rand() % 100 < MPROB) {
            type = NUM_NON_TERMS + rand()%NUM_TERMS;
            if (type == constt){
                constValue = double(drand48() * 2.0 * CONST_LIMIT) - (CONST_LIMIT/2.0);
            }
        }
        return;
    }
    else{
        if (rand() % 100 < MPROB)
            type=rand()%NUM_NON_TERMS;
        for(int i=0;i<MAX_ARITY;i++){
            if(branches[i] != NULL){
                branches[i]->mutate();
            }
        }
    }
}//mutate()

void node::trim(int desired_depth){
    if(desired_depth > 0){
        if(branches[0] != NULL)
            branches[0]->trim(desired_depth - 1);
        if(branches[1] != NULL)
            branches[1]->trim(desired_depth - 1);
    }
    else{
        //branches[0]->erase();
        //branches[1]->erase();
    }

}//trim()

/*Recursively evaluate the tree*/
double node::evaluate(double X, double X2){
    double l, r;
    switch(type){
        case add:
            l = branches[0]->evaluate(X,X2);
            r = branches[1]->evaluate(X,X2);
            return(l+r);
        case subtract:
            l = branches[0]->evaluate(X,X2);
            r = branches[1]->evaluate(X,X2);
            return(l-r);
        case multiply:
            l = branches[0]->evaluate(X,X2);
            r = branches[1]->evaluate(X,X2);
            return (l*r);
        case divide:
            l = branches[0]->evaluate(X,X2);
            r = branches[1]->evaluate(X,X2);
            if (r != 0) return(l/r);
            else return(l);
        case greater_than:
            l = branches[0]->evaluate(X,X2);
            r = branches[1]->evaluate(X,X2);
            if(l >= r)
                return l;
            else
                return r;
        case less_than:
            l = branches[0]->evaluate(X,X2);
            r = branches[1]->evaluate(X,X2);
            if(l <= r)
                return l;
            else
                return r;
        case inputX:
            return(X);
        case inputX2:
            return(X2);
        case constt:
            return(constValue);
        default:
            cout << "Error, unknown instruction " << type << endl;
            break;
    }
    return 0;
}//evaluate()

/*print function*/
void node::print_function(double X, double X2){
    switch(type){
		case add:
            cout << "(";
			branches[0] -> print_function(X,X2);
			cout << "+";
			branches[1] -> print_function(X,X2);
			cout << ") ";
			return;
		case subtract:
            cout << "[";
			branches[0] -> print_function(X,X2);
			cout << "-";
			branches[1] -> print_function(X,X2);
			cout << "] ";
			return;
        case multiply:
            cout << "{";
			branches[0] -> print_function(X,X2);
			cout << "*";
			branches[1] -> print_function(X,X2);
			cout << "} ";
			return;
		case divide:
            cout << "<";
			branches[0] -> print_function(X,X2);
			cout << "/";
			branches[1] -> print_function(X,X2);
			cout << "> ";
			return;
        case greater_than:
            cout << "(";
			branches[0] -> print_function(X,X2);
			cout << "greater than";
			branches[1] -> print_function(X,X2);
			cout << ")";
        case less_than:
            cout << "(";
			branches[0] -> print_function(X,X2);
			cout << "less than";
			branches[1] -> print_function(X,X2);
			cout << ")";
		case inputX:
			cout << " X1";
			return;
        case inputX2:
			cout << " X2";
			return;
		case constt:
            cout << " " << constValue;
            return;
		default:
			cout << "Error, unknown instruction " << type << endl;
    }
}//print_tree

/* Return amount of nodes through recursion. */
void node::calc_size(int &terms, int &non_terms){
    if(type >= NUM_NON_TERMS){	// count size
        terms++;
        return;
    }
    else{
        non_terms++;
        for(int i=0;i<2;i++){
            if(branches[i] != NULL)
                branches[i]->calc_size(terms,non_terms);

            }
    }
}//calc_size

void node::walk_terms(int &depth, node*& N){
    if (depth < 0)
        return;
    if (depth == 0) {
        N = this;
        return;
    }
    if(type >= NUM_NON_TERMS){
        depth--;
        return;
    }
    else{
        for(int i=0;i<MAX_ARITY;i++){
            if(branches[i] != NULL)
                branches[i]->walk_terms(depth, N);
        }
    }
}//walk_terms()

void node::walk_nonterms(int &depth, node*& N){
    if (depth < 0) {return;}
    if (depth == 0) {
        N = this;
        return;
    }
    if(type < NUM_NON_TERMS){
        for(int i=0;i<MAX_ARITY;i++){
            if(branches[i] != NULL){
                depth--;
                branches[i]->walk_nonterms(depth, N);
            }
        }
    }
}//walk_nonterms

void node::walk(int &depth, node*& N){
    if (depth < 0) {return;}
    if (depth == 0) {
        N = this;
        return;
    }
    if(type >= NUM_NON_TERMS){
        walk(--depth, N);
    }
    else{
        for(int i=0;i<MAX_ARITY;i++){
            if(branches[i] != NULL)
                branches[i]->walk_nonterms(--depth, N);
        }
    }
}//walk()




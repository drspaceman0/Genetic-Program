#include"population.h"

population::population(){
  //  individuals = new indiv[P_SIZE];
  fout = fopen("AvgBest.txt", "a");
}

population::~population(){
  for (int i = 0; i < P_SIZE; i++)
    individuals[i].erase();
  //delete [] individuals;
}

void population::tournament(indiv W, indiv* A){
  if(A[0].get_fitness() < A[1].get_fitness()){
    W.copy(A[0]);
  }
  else W.copy(A[1]);
  for (int i = 0; i < TOURNEY; i++){
    if (W.get_fitness() > A[i].get_fitness()){
      W.copy(A[i]);
    }
  }
}

void population::calc_all(){
  for (int i = 0; i < P_SIZE; i++){
    individuals[i].evaluate();
    individuals[i].calc_size();
  }
}

void population::new_generation(){

    indiv W[P_SIZE];// = new indiv[P_SIZE]; // Winners
    indiv Round[TOURNEY];// = new indiv[TOURNEY];
    indiv* inds = individuals; // alias to shorten long lines of code
    indiv Elite;
    int a, b;

    calc_all();



    Elite.copy(best_get());

    for (int i = 0; i < P_SIZE; i++){
        for(int j = 0; j < TOURNEY; j++){
            a = rand() % (int)(P_SIZE - 2);
            Round[j] = inds[a];
        }
        tournament(W[i], Round);
    }

    /* Crossover */
    for (int i = 0; i + 1 < P_SIZE; i += 2){
        crossover(W[i], W[i+1]);
        //W[i].the_indiv->trim(5);
        //W[i+1].the_indiv->trim(5);
    }

    /* Mutate */
    for (int i = 0; i < P_SIZE; i++){
        mutate(W[i]);
    }

    for(int i = 0; i < P_SIZE; i++){
        if (inds[i].the_indiv != NULL)
            inds[i].erase();
    }

    for(int i = 0; i < P_SIZE; i++)
        inds[i] = W[i];

    /* Elitism */
    a = rand() % (int)(P_SIZE - 2);
    b = rand() % (int)(P_SIZE - 2);
    inds[a].copy(Elite);
    inds[b].copy(Elite);

    calc_all();

    /*get rid of worst individual, grow new one*/


    //W->erase();
}

void population::crossover(indiv A, indiv B){
    node* temp = new node;
    node* pos1;
    node* pos2;
    int r;
    int range;

    if (rand() % 100 < 90) {
        A.calc_size();
        range = A.get_nonterms();
        r = rand() % (int)(range + 1);
        A.walk_nonterms(r, pos1);
    }
    else {
        A.calc_size();
        range = A.get_terms();
        r = rand() % (int)(range + 1);
        A.walk_terms(r, pos1);
    }
    if (rand() % 100 < 90) {
        B.calc_size();
        range = B.get_nonterms();
        r = rand() % (int)(range + 1);
        B.walk_nonterms(r, pos2);
    }
    else {
        B.calc_size();
        range = B.get_terms();
        r = rand() % (int)(range + 1);
        B.walk_terms(r, pos2);
    }

    try{
        temp->copy(pos1, pos1->parent);
        pos1->copy(pos2, pos2->parent);
        pos2->copy(temp, temp->parent);
    }
    catch(...){
        cout << "Segmentation fault" <<endl;
    }


    temp->erase();
}

void population::mutate(indiv A){
    A.mutate();
}

indiv population::worst_get(){
    double temp;
    int count = 0;
    double maxF = -999999999;
    for (int i = 0; i < P_SIZE; i++) {
        temp = individuals[i].evaluate();
        if (temp >= maxF) {
            maxF = temp;
            count = i;
        }
    }
    return individuals[count];
}

int population::return_worst_position(){
    double temp;
    int count = 0;
    double maxF = -999999999;
    for (int i = 0; i < P_SIZE; i++) {
        temp = individuals[i].evaluate();
        if (temp >= maxF) {
            maxF = temp;
            count = i;
        }
    }
    return count;
}


double population::avg_fit_get(){
    double sum = 0;
    for (int i = 0; i < P_SIZE; i++){
        sum += individuals[i].evaluate();
    }
    return (sum / P_SIZE);
}

indiv population::best_get(){
    double temp;
    double minF = individuals[0].get_fitness();
    int index = 0;
    for (int i = 0; i < P_SIZE; i++) {
        temp = individuals[i].get_fitness();
        if (temp <= minF){
            minF = temp;
            index = i;
        }
    }
    return individuals[index];
}

int population::avg_size_get(){
    double sum = 0;
    for (int i = 0; i < P_SIZE; i++){
        sum += individuals[i].get_size();
    }
    int avg = sum/P_SIZE;
    return avg;
}

int population::max_size_get(){
    int temp;
    int maxS = individuals[0].calc_size();
    for (int i = 0; i < P_SIZE; i++) {
        temp = individuals[i].get_size();
        if (temp > maxS){
            maxS = temp;
        }
    }
    return maxS;
}

int population::min_size_get(){
    int temp;
    int minS = individuals[0].calc_size();
    for (int i = 0; i < P_SIZE; i++) {
        temp = individuals[i].get_size();
        if (temp < minS){
            minS = temp;
        }
    }
    return minS;
}

void population::populate() {
    //  individuals = new indiv[P_SIZE];
    for (int i = 0; i < P_SIZE; i++) {
        individuals[i].generate(MAX_DEPTH);
    }
}

//adding write to file function
void population::evaluate_population(){
    //calc_all();
    indiv best = best_get();
    indiv worst = worst_get();

    cout << "Average size: " << avg_size_get() << endl;
    cout << "Average fit: " << avg_fit_get() << endl;

    cout << "Best size: " << best.get_size() << endl;
    cout << "Best fit: " << best.get_fitness() << endl;

    cout << "Worst size: " << worst.get_size() << endl;
    cout << "Worst fit: " << worst.get_fitness() << endl << endl;

}


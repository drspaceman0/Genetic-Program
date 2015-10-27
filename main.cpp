// Greater than, less than increase avg fit by 15
// apply size check, subtree mutation
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

#include"population.h"

using namespace std;

int main() {
    srand((unsigned)time(NULL));
    population p;
    p.populate();

    cout << "\nInitial:";
    cout << "\n--------------------";
    p.evaluate_population();
/*
  ofstream myfile;
    myfile.open("/home/eric/Desktop/result.txts", ios::app);
    if(myfile.is_open()){


        myfile.close();
    }
*/
    //for (int i = 0; i < 300; i++){
    int i = 1;
    while(p.best_get().get_fitness() != 0){
        cout << i << endl;
        i++;
        p.new_generation();
        p.evaluate_population();

        //myfile << p.best_get().get_fitness() << " ";
        //myfile << p.worst_get().get_fitness() << " ";
        //myfile << p.avg_print() << " ";
        //myfile << endl;
        if(p.best_get().get_fitness() == 0){
            break;
        }
    }
    //myfile.close();
    cout << "\nFinal:";
    cout << "\n--------------------";
    p.evaluate_population();
    //p.worst_get().print_indiv_tree(1,2);
    return 1;
}

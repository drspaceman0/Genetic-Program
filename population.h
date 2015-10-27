#ifndef POPULATION_H
#define POPULATION_H

#include"indiv.h"
class population{
    public:
        FILE* fout;
        indiv individuals[P_SIZE];
        population();
        ~population();
        void mutate(indiv);
        void crossover(indiv, indiv);
        void tournament(indiv, indiv*);
        void new_generation();

        void calc_all();
        indiv best_get();
        indiv worst_get();
        double avg_fit_get();
        int avg_size_get();
        int max_size_get();
        int min_size_get();
        void populate();
        void evaluate_population();
        int return_worst_position();
};

#endif POPULATION_H

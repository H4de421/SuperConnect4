#include "Board_managment.hh"

struct stratagem {
    int total_size;
    int current;
    int buffer[8];
    void (*function)(int *tab, int col); 
    int cost;
};

void strat_fun_500k(int* tab, int col);
void strat_fun_mine(int* tab, int col);
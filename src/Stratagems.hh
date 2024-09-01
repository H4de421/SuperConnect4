#include "Board_managment.hh"
#include <unistd.h>

struct stratagem {
    int total_size;
    int current;
    int buffer[8];
    int cost;
    int max_charges;
    int charges;
    int max_reload;
    int reload;
    bool in_reload;
    bool in_action;
    void (*function)(int *tab, int col); 
    char name[15];
    bool got_rout;
    int rout_id;
    int rout_duration;
};

void reload_all(struct stratagem *strats[4], int NB_strats);

void strat_reload(struct stratagem *strat);

void strat_fun_500k(int* tab, int col);

void strat_fun_mine(int* tab, int col);

void strat_fun_barrage(int *tab, int col);

void strat_rout_barrage(int *tab);

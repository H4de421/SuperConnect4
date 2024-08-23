#include "Stratagems.hh"

void strat_fun_500k(int* tab, int col)
{
    int i = col;
    tab[i] = 2;
    print_grid(tab);
    while (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 0) 
    {
        tab[i] = 0;
        tab[i + NB_Columns] = 2;
        print_grid(tab);
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // = sleep(0.075)
        i += NB_Columns;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    tab[i] = 0;
}

void strat_fun_mine(int* tab, int col)
{
    int i = col;
    tab[i] = 3;
    print_grid(tab);
    while (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 0) 
    {
        tab[i] = 0;
        tab[i + NB_Columns] = 3;
        print_grid(tab);
        std::this_thread::sleep_for(std::chrono::milliseconds(150   )); // = sleep(0.075)
        i += NB_Columns;
    }
}
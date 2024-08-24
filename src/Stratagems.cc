#include "Stratagems.hh"

void strat_fun_500k(int* tab, int col)
{
    /* drop part */
    int i = col;
    tab[i] = 2;
    print_grid(tab);
    while (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 0) 
    {
        tab[i] = 0;
        tab[i + NB_Columns] = 2;
        print_grid(tab);
        std::this_thread::sleep_for(std::chrono::milliseconds(75)); // = sleep(0.075)
        i += NB_Columns;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    /* democratic part */
    if (i + NB_Columns < NB_Rows*NB_Columns)
    {
        tab[i+NB_Columns] = 0;
    }
    if (i + 2*NB_Columns < NB_Rows*NB_Columns)
    {
        tab[i+2*NB_Columns] = 0;
    }
    if (i%NB_Columns > 0)
    {
        i--;
        if (i + NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+NB_Columns] = 0;
        }
        if (i + 2*NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+2*NB_Columns] = 0;
        }
        i++;
    }
    if (i%NB_Columns < 6)
    {
        i++;
        if (i + NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+NB_Columns] = 0;
        }
        if (i + 2*NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+2*NB_Columns] = 0;
        }
        i--;
    }
    tab[i] = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    print_grid(tab);
    aply_gravity(tab);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(75)); // = sleep(0.075)
        i += NB_Columns;
    }
}
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
        tab[i+NB_Columns] = (tab[i+NB_Columns]==11? 1:0);
    }
    if (i + 2*NB_Columns < NB_Rows*NB_Columns)
    {
        tab[i+2*NB_Columns] = (tab[i+2*NB_Columns]==11? 1:0);
    }
    if (i%NB_Columns > 0)
    {
        i--;
        if (i + NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+NB_Columns] = (tab[i+NB_Columns]==11? 1:0);
        }
        if (i + 2*NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+2*NB_Columns] = (tab[i+2*NB_Columns]==11? 1:0);
        }
        i++;
    }
    if (i%NB_Columns < 6)
    {
        i++;
        if (i + NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+NB_Columns] = (tab[i+NB_Columns]==11? 1:0);
        }
        if (i + 2*NB_Columns < NB_Rows*NB_Columns)
        {
            tab[i+2*NB_Columns] = (tab[i+2*NB_Columns]==11? 1:0);
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

void reload_all(struct stratagem *strats[4], int NB_strats)
{
    for (int i = 0; i < NB_strats; i++)
    {
        strat_reload(strats[i]);
    }
}

void strat_reload(struct stratagem *strat)
{
    if (strat->in_reload)
    {
        strat->reload--;
        if (strat->reload == 0)
        {
            strat->charges = strat->max_charges;
            strat->reload = strat->max_reload;
            strat->in_reload = false;
        }
    }
    if (!strat->in_action && !strat->in_reload && strat->charges == 0)
    {
        strat->in_reload = true;
        strat->reload = strat->max_reload;
    }
}

void drop_bomb(int *tab, int col)
{
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
    if (i + NB_Columns < NB_Rows*NB_Columns)
    {
        tab[i+NB_Columns] = (tab[i+NB_Columns]==11? 1:0);;
    }
    tab[i] = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    print_grid(tab);
}

void strat_fun_barrage(int *tab, int col)
{

}

void strat_rout_barrage(int *tab)
{
    srand(time(NULL));
    drop_bomb(tab, rand()%5);
    drop_bomb(tab, rand()%5);
    drop_bomb(tab, rand()%5);
}
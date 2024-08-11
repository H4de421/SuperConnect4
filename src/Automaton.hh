#include "Board_managment.hh"
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


struct windows_stats
{
    int automaton;
    int player;
    int empty;
};

//int* tab_copy(int *tab);

int automaton_thought_maker(int *tab, int difficulty);

int automaton_MinMax_thing(int *tab, int deep, bool player_turn);

int automaton_threat_evaluation(int *tab);

int automaton_score(struct windows_stats *stats);

struct windows_stats *automaton_window_analyser(int *win, int size);
#include "Automaton.hh"

int automaton_thought_maker(int *tab, int difficulty)
{
    int res = 0;
    int value = INT_MIN;
    for(int i = 0; i<NB_Columns; i++)
    {
        if (colomn_is_full(tab, i))
        {
            continue;
        }
        int* tab_c = copy_board(tab);
        drop_piece(tab_c, i, -1);
        int score = automaton_MinMax_thing(tab_c, difficulty, false); 
        if (score > value)
        {
            res = i;
            value = score;
        }
        free(tab_c);
    }
    return res;//automaton_MinMax_thing(tab, 8, false);
}

int automaton_MinMax_thing(int *tab, int deep, bool player_turn)
{
    if (deep==0)
    {
        return automaton_threat_evaluation(tab);
    }
    srand(time(NULL));   // Initialization, should only be called once.
    if (player_turn)
    {
        int value = INT_MAX;
        for (int i = 0;i<7;i++)
        {
            if (colomn_is_full(tab, i))
            {
                continue;
            }
            int* tab_c = copy_board(tab);
            drop_piece(tab_c, i, -1);
            int score = automaton_MinMax_thing(tab_c, deep-1, false); 
            if (score < value)
            {
                value = score;
            }
            free(tab_c);
        }
        return value;
    }
    else
    {
        int value = INT_MIN;
        for (int i = 0;i<7;i++)
        {
            if (colomn_is_full(tab, i))
            {
                continue;
            }
            int* tab_c = copy_board(tab);
            drop_piece(tab_c, i, -1);
            int score = automaton_MinMax_thing(tab_c, deep-1, true); 
            if (score > value)
            {
                value = score;
            }
            free(tab_c);
        }
        return value;
    }
}

int automaton_threat_evaluation(int *tab)
{
    int score = 0;

    /* center check */
    int* col = get_raw(tab, 3);
    struct windows_stats* win_info = automaton_window_analyser(col, NB_Rows);
    score+=win_info->automaton*3;

    /* raw check */
    for(int r = 0; r < NB_Rows; r++)
    {
        int* row = get_raw(tab, r);
        for (int i =0; i< NB_Columns-3; i++)
        {
            int* wind = (int*)malloc(4*sizeof(int));
            wind = (int*)memcpy(wind, row+i, 4*sizeof(int));
            struct windows_stats* win_info = automaton_window_analyser(wind,4);
            score+= automaton_score(win_info);
            free(win_info);
            free(wind);
        }
        free(row);
    }
    /* column check */
    for(int c = 0; c < NB_Columns; c++)
    {
        int* col = get_raw(tab, c);
        for (int i =0; i< NB_Rows-3; i++)
        {
            int* wind = (int*)malloc(4*sizeof(int));
            wind = (int*)memcpy(wind, col+i, 4*sizeof(int));
            struct windows_stats* win_info = automaton_window_analyser(wind,4);
            score+= automaton_score(win_info);
            free(win_info);
            free(wind);
        }
        free(col);
    }

    /* diag1 check */
    for(int r = 0; r < NB_Rows-3; r++)
    {
        for(int c = 0; c < NB_Columns-3; c++)
        {
            int *wind = get_diag1(tab, r, c);
            struct windows_stats* win_info = automaton_window_analyser(wind,4);
            score+=automaton_score(win_info);
            free(wind);
        }
    }

    /* diag2 check */
    for(int r = 0; r < NB_Rows-3; r++)
    {
        for(int c = 0; c < NB_Columns-3; c++)
        {
            int *wind = get_diag2(tab, r, c);
            struct windows_stats* win_info = automaton_window_analyser(wind,4);
            score+=automaton_score(win_info);
            free(wind);
        }
    }
    return score;
}

int automaton_score(struct windows_stats *stats)
{
    int score = 0;

    if (stats->automaton == 4)
    {
        score += 100;
    }
    else if (stats->automaton == 3 && stats->empty == 1)
    {
        score += 10;
    }
    else if (stats->automaton == 2 && stats->empty == 2)
    {
        score += 2;
    }

    if (stats->player==3 && stats->empty == 1)
    {
        score-= 4;
    }
    return score;
}

struct windows_stats *automaton_window_analyser(int *win, int size)
{
    struct windows_stats *res = (struct windows_stats *)malloc(sizeof(struct windows_stats));
    for (int i = 0; i< size; i++)
    {
        if (win[i]==1)
        {
            res->player++;
        }
        else if (win[i]==0)
        {
            res->empty++;
        }
        else
        {
            res->automaton++;
        }
    }
    return res;
}

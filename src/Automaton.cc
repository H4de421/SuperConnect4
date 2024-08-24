#include "Automaton.hh"
#include <unistd.h>

int automaton_thought_maker(int *tab, int difficulty)
{
    int res = 0;
    int value = INT_MIN;
    int values[7] = {0,0,0,0,0,0,0};
    for(int i = 0; i<NB_Columns; i++)
    {
        if (colomn_is_full(tab, i))
        {
            values[i] = -1;
            continue;
        }
        // changer the board
        drop_piece(tab, i, -1);
        
        int score = automaton_MinMax_thing(tab, difficulty-1, true, get_first_piece(tab, i), i, INT_MIN, INT_MAX); 
        // restore the board
        del_first_piece(tab, i);

        values[i] = score;  
        if (score > value)
        {
            res = i;
            value = score;
        }
    }
    /*printf("values = |");
    for (int i = 0; i< 7; i++)
    {
        printf(" %d |", values[i]);
    }
    printf("  so the bot choosed %dth column ", res);*/

    return res;
}

int automaton_MinMax_thing(int *tab, int deep, bool player_turn, int old_x, int old_y, int alpha, int beta)
{
    bool ended = game_finished(tab, old_x, old_y);
    if (ended || deep==0)
    {
        if (ended)
        {
            return (player_turn)? INT_MAX : INT_MIN;
        }
        else
        {
            return automaton_threat_evaluation(tab);
        }
    }
    srand(time(NULL));   // Initialization, should only be called once.
    if (player_turn)
    {
        int value = INT_MAX;
        int col_played = -1;
        for (int i = 0;i<7;i++)
        {
            if (colomn_is_full(tab, i))
            {
                continue;
            }
        
            drop_piece(tab, i, 1);
            int score = automaton_MinMax_thing(tab, deep-1, false, get_first_piece(tab, i), i, alpha, beta); 
            del_first_piece(tab, i);
            if (score < value)
            {
                value = score;
                col_played = i;
            }
            beta = beta > value ? value : beta ;
            if (alpha >= beta)
				break;
        }
        //D printf("player played col %d with score = %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", col_played, value);
        //D print_grid(tab);
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
            drop_piece(tab, i, -1);
            int score = automaton_MinMax_thing(tab, deep-1, false, get_first_piece(tab, i), i, alpha, beta); 
            del_first_piece(tab, i);
            if (score > value)
            {
                value = score;
            }
            alpha = alpha > value ? alpha : value;
            if (alpha >= beta)
				break;
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
            score += automaton_score(win_info);
            free(win_info);
            free(wind);
        }
        free(row);
    }
    
    /* column check */
    for(int c = 0; c < NB_Columns; c++)
    {
        int* col = get_col(tab, c);
        for (int i =0; i< NB_Rows-2; i++)
        {
            int* wind = (int*)malloc(4*sizeof(int));
            wind = (int*)memcpy(wind, col+i, 4*sizeof(int));

            struct windows_stats* win_info = automaton_window_analyser(wind,4);
            score += automaton_score(win_info);
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
            score +=automaton_score(win_info);
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
            score +=automaton_score(win_info);
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
        score += 1000;
    }
    if (stats->automaton == 3 && stats->empty == 1)
    {
        score += 100;
    }
    else if (stats->automaton == 2 && stats->empty == 2)
    {
        score += 20;
    }

    if (stats->player==3 && stats->empty == 1)
    {
        score -= 300;
    }
    else if (stats->player==2 && stats->empty == 2)
    {
        score -= 1000;
    }
    return score;
}

struct windows_stats *automaton_window_analyser(int *win, int size)
{
    struct windows_stats *res = (struct windows_stats *)calloc(1,sizeof(struct windows_stats));
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
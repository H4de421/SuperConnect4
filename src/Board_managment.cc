#include "Board_managment.hh"

bool game_finished(int *tab, int x, int y)
{
    return check(tab, x, y, 1, -1) ||
           check(tab, x, y, 1, 1) ||
           check(tab, x, y, 1, 0) ||
           check(tab, x, y, 0, 1); 
}

bool check(int *tab, int x, int y, int r, int c)
{
    int p = tab[x * NB_Columns + y];
    if (p == 0)
    {
        printf("x:%d y:%d \n", x, y);
        perror("Bad placement, player == 0. Can't be possible :\n");
    }
    int score1 = sub_check(tab, x, y, p, r, c);
    int score2 = sub_check(tab, x, y, p, -r, -c);
    return score1 + score2 + 1 >= 4;
}

int sub_check(int *tab, int x, int y, int player, int r, int c)
{ 
    x += r;
    y += c;
    if (x * NB_Columns + y >= 0 && x * NB_Columns + y <= NB_Columns * NB_Rows &&
        tab[x * NB_Columns + y] == player) 
    {
        return sub_check(tab, x, y, player, r, c) + 1;
    }
    return 0;
}

bool colomn_is_full(int *tab, int c) { return tab[0 * 0 + c] != 0; }

/* put a {player}'color pawn at the top of the {column} */
struct coo update_grid(int *tab, int player, int column, struct coo *moove_piece)
{
    moove_piece->y = column;
    int i = column;
    tab[i] = player;
    print_grid(tab);
    while (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 0) 
    {
        tab[i] = 0;
        tab[i + NB_Columns] = player;
        print_grid(tab);
        std::this_thread::sleep_for(std::chrono::milliseconds(75)); // = sleep(0.075)
        i += NB_Columns;
    }
    moove_piece->x = i / NB_Columns;
    return *moove_piece;
}

void drop_piece(int *tab, int column, int player)
{
    int deep = 0;
    while (deep+1<NB_Rows && tab[(deep+1)*NB_Columns+column]==0)
    {
        deep+=1;
    }
    tab[deep*NB_Columns+column] = player;
}

void del_first_piece(int *tab, int column)
{
    int deep = get_first_piece(tab, column);
    tab[deep*NB_Columns+column] = 0;
}

int* copy_board(int *tab)
{
    int * res = (int*)malloc(NB_Rows * NB_Columns * sizeof(int));
    for (int i = 0; i < NB_Rows * NB_Columns ; i++)
    {
        res[i] = tab[i];
    }
    return res;
}

void print_grid(int *tab) 
{
    printf("\r\033[19A \n");
    printf("\033[8C                             \033[29D\033[1B                             \033[29D\033[1B                             \033[29D\033[1B");
    for (int x = 0; x < NB_Rows; x++) 
    {
        printf("\r\t╠─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╣\033[1B\r\t");
        for (int y = 0; y < NB_Columns; y++) 
        {
            if (tab[x * NB_Columns + y] == 1)
                printf("║ \033[0;34m■ \033[0m");
            else if (tab[x * NB_Columns + y] == -1)
                printf("║ \033[0;31m■ \033[0m");
            else
                printf("║   ");
        }
        printf("║\033[1B\r");
    }
    printf("\t╚═══╩═══╩═══╩═══╩═══╩═══╩═══╝\033[3B\r");
}

int *get_raw(int *tab, int shift)
{
    int *res = (int*)malloc(NB_Columns*sizeof(int));
    for (int i =0; i<NB_Columns; i++)
    {
        res[i]=tab[shift*NB_Columns+i];
    }
    return res;
}

int *get_col(int *tab, int shift)
{
    int *res = (int*)malloc(NB_Rows*sizeof(int));
    for (int i =0; i<NB_Rows; i++)
    {
        res[i]=tab[i*NB_Columns+shift];
    }
    return res;
}

int *get_diag1(int *tab, int r, int c)
{
    int *res = (int*)malloc(NB_Rows*sizeof(int));
    for (int i =0; i<NB_Rows; i++)
    {
        res[i]=tab[(r+i)*NB_Columns+c+i];
    }
    return res;   
}

int *get_diag2(int *tab, int r, int c)
{
    int *res = (int*)malloc(NB_Rows*sizeof(int));
    for (int i =0; i<NB_Rows; i++)
    {
        res[i]=tab[(r+3-1)*NB_Columns+c+i];
    }
    return res;   
}

/* return the raw of the higher piece in the column {column}*/
int get_first_piece(int *tab, int column)
{
    /*if (colomn_is_full(tab, column))
    {
        return 0;
    }*/
    int deep = 0;
    while (deep<NB_Rows && tab[deep*NB_Columns+column]==0)
    {
        deep+=1;
    }
    return deep;
}
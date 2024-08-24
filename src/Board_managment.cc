#include "Board_managment.hh"

#include <unistd.h>

bool game_finished(int *tab, int x, int y)
{
    //return false;
    int player = tab[x*NB_Columns+y];
    int down = 1 + check_down(tab, x+1, y, player, 3);
    int line = 1 + check_line(tab, x, y+1, player, 3, 1) + check_line(tab, x, y-1, player, 3, -1);
    int diag1 = 1 + check_diag1(tab, x+1, y+1, player, 3, 1) + check_diag1(tab, x-1, y-1, player, 3, -1);
    int diag2 = 1 + check_diag2(tab, x+1, y-1, player, 3, 1) + check_diag2(tab, x-1, y+1, player, 3, -1);
    /*printf("down = %d\nline = %d\ndiag1 = %d\ndiag2 = %d\n", down, line, diag1, diag2);
    printf("1-> %d \n", check_diag1(tab, x+1, y+1, player, 3, 1));
    printf("2-> %d \n", check_diag1(tab, x-1, y-1, player, 3, -1));*/
    return down >= 4 ||
           line >= 4 ||
           diag1 >= 4 ||
           diag2 >= 4;
}

int check_down(int *tab, int x, int y, int player, int deep)
{
    if (deep == 0 || x == NB_Columns)
    {
        return 0;
    }
    if (tab[x*NB_Columns+y] == player)
    {
        return 1 + check_down(tab, x+1, y, player, deep-1);
    }
    return 0;
}

int check_line(int *tab, int x, int y, int player, int deep, int shift)
{
    if (deep == 0 || y == NB_Columns || y < 0)
    {
        return 0;
    }
    if (tab[x*NB_Columns+y] == player)
    {
        return 1 + check_line(tab, x, y+shift, player, deep-1, shift);;
    }
    return 0;
}

/* \ */
int check_diag1(int *tab, int x, int y, int player, int deep, int shift)
{
    if (deep == 0 || (x*NB_Columns+y) < 0 || (x*NB_Columns+y) > NB_Columns*NB_Rows)
    {
        return 0;
    }
    if (tab[x*NB_Columns+y] == player)
    {
        return 1 + check_diag1(tab, x+shift, y+shift, player, deep-1, shift);
    }
    return 0;
}

/* / */
int check_diag2(int *tab, int x, int y, int player, int deep, int shift)
{
    if (deep == 0)
    {
        return 0;
    }
    if ( x < 0 || x == NB_Rows || y == NB_Columns || y < 0 )
    {
        return deep==0;
    }
    if (tab[x*NB_Columns+y] == player)
    {
        return 1 + check_diag2(tab, x+shift, y-shift, player, deep-1, shift);
    }
    return 0;
}

/*
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
*/
bool colomn_is_full(int *tab, int c) { return tab[0 * 0 + c] != 0; }

/* put a {player}'color pawn at the top of the {column} */
bool update_grid(int *tab, int player, int column, struct coo *moove_piece)
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
    if (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 3)
    {
        tab[i] = 0;
        tab[i + NB_Columns] = player;
        print_grid(tab);
        std::this_thread::sleep_for(std::chrono::milliseconds(75)); // = sleep(0.075)
        // explosion
        tab[i + NB_Columns] = 0;
        print_grid(tab);
        return false;
    }
    moove_piece->x = i / NB_Columns;
    return true;
}

void drop_piece(int *tab, int column, int player)
{
    int deep = 0;
    while (deep+1<NB_Rows && tab[(deep+1)*NB_Columns+column]==0)
    {
        deep+=1;
    }
    if ((deep+1<NB_Rows && tab[(deep+1)*NB_Columns+column]!=2) || deep+1==NB_Rows)
    {
        tab[deep*NB_Columns+column] = player;
    }
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
    printf("\r\t╠─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╣\033[1B\r\t");
    for (int x = 0; x < NB_Rows; x++) 
    {
        if (x == NB_Rows-1)
        {
            printf("\r\033[1B\t╚═══╩═══╩═══╩═══╩═══╩═══╩═══╝\r\t\033[1A");
        }
        else
        {
            printf("\r\033[1B\t╠─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╣\033[1A\r\t");
        }
        for (int y = 0; y < NB_Columns; y++) 
        {
            if (tab[x * NB_Columns + y] == 3)
                printf("║ \033[0;33m \033[1D\033[1B▀\033[1A \033[0m");
            else if (tab[x * NB_Columns + y] == 2)
                printf("║ \033[0;33m█ \033[0m");
            else if (tab[x * NB_Columns + y] == 1)
                printf("║ \033[0;34m■ \033[0m");
            else if (tab[x * NB_Columns + y] == -1)
                printf("║ \033[0;31m■ \033[0m");
            else
                printf("║   ");
        }
        printf("║\033[2B\r");
    }
    printf("\033[2B\r");
    fflush(stdout);
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

void col_colapse(int *tab, int col, int deep)
{
    int pos = deep*NB_Columns+col;
    for (int i = deep; i > 0; i--)
    {
        tab[pos] = tab[pos-NB_Columns];
        pos -= NB_Columns;
    }
    tab[col] = 0;
}

void aply_gravity(int *tab)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    bool as_fell = true;
    while (as_fell)
    {
        as_fell = false;
        for(int raw = NB_Rows-1; raw > 0; raw--)
        {
            for(int col = 0; col < NB_Columns; col++)
            {
                if (tab[raw*NB_Columns+col] == 0 && tab[(raw-1)*NB_Columns+col] != 0)
                {
                    col_colapse(tab, col, raw);
                    as_fell = true;
                }
            }
            print_grid(tab);
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
        }
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
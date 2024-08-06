#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NB_Rows 6
#define NB_Colums 7

struct coo
{
    int x;
    int y;
};


void print_grid(int *tab)
{
    for (int x = 0; x < NB_Rows; x++)
    {
        printf("--------------------------\n");
        for (int y = 0; y < NB_Colums; y++)
        {
            printf("| %d ", tab[x * NB_Colums + y]);
        }
        printf("|\n");
    }
    printf("--------------------------\n");
}

int sub_check(int *tab, int x, int y, int player, int r, int c)
{
    x += r;
    y += c;
    if (x * NB_Colums + y >= 0 && x * NB_Colums + y <= NB_Colums*NB_Rows && tab[x * NB_Colums + y] == player)
    {
        return sub_check(tab, x, y, player, r, c) + 1;
    }
    return 0;
}

bool check(int *tab, int x, int y, int r, int c)
{
    int p = tab[x * NB_Colums + y];
    int score1 = sub_check(tab, x, y, p, r, c);
    int score2 = sub_check(tab, x, y, p, -r, -c);
    printf("Score : %d\n", score1+score2+1);
    return score1 + score2 + 1 >= 4;
}

int main()
{
    bool end = false;
    int *tab = calloc(NB_Rows * NB_Colums, sizeof(int));
    struct coo *last = malloc(sizeof(struct coo));
    tab[0*NB_Colums + 0] = -1;
    tab[0*NB_Colums + 1] = -1;
    tab[0*NB_Colums + 2] = -1;
    tab[0*NB_Colums + 3] = -1;
    while (end != true)
    {
        last->x = 0;
        last->y = 3;

        if(check(tab,last->x,last->y,1,-1) || 
           check(tab,last->x,last->y,1, 1) || 
           check(tab,last->x,last->y,1,0) || 
           check(tab,last->x,last->y,0,1)) end = true;
    }

    // printf("[CLIENT]:helle world!\n");

    print_grid(tab);
    if(end){
        printf("BRAVO !");
    }
    free(tab);
}
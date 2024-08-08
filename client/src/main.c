#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define NB_Rows 6
#define NB_Columns 7

struct coo
{
    int x;
    int y;
};


void print_grid(int *tab)
{
    printf("\033[15A \n");
    for (int x = 0; x < NB_Rows; x++)
    {
        printf("            ╠─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╣\n");
        printf("            ");
        for (int y = 0; y < NB_Columns; y++)
        {
            if(tab[x * NB_Columns + y] == 1)
            printf("║ \033[0;31m■ \033[0m");
            else if(tab[x * NB_Columns + y] == -1) printf("║ \033[0;33m■ \033[0m");
            else printf ("║ X ");
        }
        printf("║\n");
    }
    printf("            ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n");
}

bool colomn_is_full(int *tab, int c)
{
    return tab[0 * 0 + c] != 0;
}

struct coo moove(int *tab, int player)
{
    int choice = 0;
    struct coo *moove_piece = malloc(sizeof(struct coo));

    do
    {
        printf("Choose a column between 1 and 7 : ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 7)
        {
            printf("Out of bound, choose a valid entry.\n\n");
            while(getchar() != '\n');
        }
    }while (choice < 1 || choice > 7);

    choice--;
    moove_piece->y = choice;
    if(!colomn_is_full(tab, choice))
    {
        for (int i = NB_Rows-1; i >= 0 ; i--)
        {
            if (tab[i * NB_Columns + choice] == 0)
            {
                tab[i * NB_Columns + choice] = player;
                moove_piece->x = i;
                break;
            }
        }
    }
    else{
        printf("\033[1AOOB\n");
    }
    return *moove_piece;
}

int sub_check(int *tab, int x, int y, int player, int r, int c)
{
    x += r;
    y += c;
    if (x * NB_Columns + y >= 0 && x * NB_Columns + y <= NB_Columns*NB_Rows && tab[x * NB_Columns + y] == player)
    {
        return sub_check(tab, x, y, player, r, c) + 1;
    }
    return 0;
}

bool check(int *tab, int x, int y, int r, int c)
{
    int p = tab[x * NB_Columns + y];
    if(p == 0) perror("Bad placement, player == 0. Can't be possible\n");
    int score1 = sub_check(tab, x, y, p, r, c);
    int score2 = sub_check(tab, x, y, p, -r, -c);
    return score1 + score2 + 1 >= 4;
}

int main()
{
    bool end = false;
    int *tab = calloc(NB_Rows * NB_Columns, sizeof(int));
    struct coo *last = malloc(sizeof(struct coo));
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    print_grid(tab);
    while (end != true)
    {
        *last = moove(tab, 1);
        print_grid(tab);
        end = check(tab,last->x,last->y,1,-1) || 
           check(tab,last->x,last->y,1, 1) || 
           check(tab,last->x,last->y,1,0) || 
           check(tab,last->x,last->y,0,1);
        if(end) break;
        
        *last = moove(tab, -1);
        print_grid(tab);
        end = check(tab,last->x,last->y,1,-1) || 
           check(tab,last->x,last->y,1, 1) || 
           check(tab,last->x,last->y,1,0) || 
           check(tab,last->x,last->y,0,1);
    }

    // printf("[CLIENT]:helle world!\n");

    // print_grid(tab);
    printf("\n\n  ____                         _ \n |  _ \\                       | |\n | |_) |_ __ __ ___   _____   | |\n |  _ <| '__/ _` \\ \\ / / _ \\  | |\n | |_) | | | (_| |\\ V / (_) | |_|\n |____/|_|  \\__,_| \\_/ \\___/  (_)\n\n");

    free(tab);
}
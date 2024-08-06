#include <stdio.h>
#include <stdlib.h>

#define NB_Rows 6
#define NB_Colums 7

// struct tab
// {
//     int i;
//     int j;
//     int val;
// };

void print_grid(int *tab)
{
    for (int i=0; i < NB_Rows; i++){
        printf("--------------------------\n");
        for (int j=0; j < NB_Colums; j++){
            printf("| %d ", tab[i*NB_Colums+j]);
        }
        printf("|\n");
    }
    printf("--------------------------\n");
}

int main()
{
    int *tab = calloc(NB_Rows*NB_Colums, sizeof(int));

    // printf("[CLIENT]:helle world!\n");

    print_grid(tab);
    free(tab);
}
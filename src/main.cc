#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define NB_Rows 6
#define NB_Columns 7

struct coo {
  int x;
  int y;
};

char getch (void)
{

    fflush(stdout);
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    struct termios aa = raw;
    aa.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, & aa);

    char ch;
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, & raw);
    return ch;
}

void print_cursor(int cursor)
{
  printf("\033[19A \n\t\t\t");
  printf("\033[%dC", (1+4*cursor));
  printf("┌─┐\033[1B\033[3D│ │\033[1B\033[3D╲_/\033[16B\r");
}

void print_grid(int *tab) {
  printf("\033[19A \n");
  printf("\33[2K\033[1B\33[2K\033[1B\33[2K\033[1B");
  for (int x = 0; x < NB_Rows; x++) {
    printf("\r\t\t\t╠─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╬─ ─╣\033[1B\r\t\t\t");
    for (int y = 0; y < NB_Columns; y++) {
      if (tab[x * NB_Columns + y] == 1)
        printf("║ \033[0;31m■ \033[0m");
      else if (tab[x * NB_Columns + y] == -1)
        printf("║ \033[0;33m■ \033[0m");
      else
        printf("║ X ");
    }
    printf("║\033[1B\r");
  }
  printf("\t\t\t╚═══╩═══╩═══╩═══╩═══╩═══╩═══╝\033[3B\r");
}

bool colomn_is_full(int *tab, int c) { return tab[0 * 0 + c] != 0; }

/*
struct coo moove(int *tab, int player) {
  int choice = 0;
  struct coo *moove_piece = (struct coo *)malloc(sizeof(struct coo));

  // input handeling 
  do {
    printf("Choose a column between 1 and 7 : ");
    scanf("%d", &choice);
    printf("\033[1A");
    if (choice < 1 || choice > 7) {
      printf("Out of bound, choose a valid entry.\n\n");
    }
    if (colomn_is_full(tab, choice - 1)) {
      printf("column is full, choose a valid entry.\n\n");
    }
  } while (choice < 1 || choice > 7);

  // updating the tab 
  choice--;
  moove_piece->y = choice;
  int i = choice;
  tab[i] = player;
  print_grid(tab);
  while (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 0) {
    tab[i] = 0;
    tab[i + NB_Columns] = player;
    print_grid(tab);
    sleep(1);
    i += NB_Columns;
  }
  moove_piece->x = i / NB_Columns;
  return *moove_piece;
}
*/

/* update the {cursor} with user input and return True id the input is validate*/
int input_handeler(char input, int *cursor)
{
  bool res = false;
  switch (input)
  {
  case 'd':
    *cursor += (*cursor < 6)? 1:0;
    break;
  case 'q':
    *cursor -= (*cursor > 0)? 1:0;
    break;
  case 's':
    res = true;
    break;
  default:
    break;
  }
  return res;
}

/* put a {player}'color pawn at the top of the {column} */
struct coo update_grid(int *tab, int player, int column)
{
  struct coo *moove_piece = (struct coo *) malloc(sizeof(struct coo));
  moove_piece->y = column;
  int i = column;
  tab[i] = player;
  print_grid(tab);
  while (i + NB_Columns < NB_Columns * NB_Rows && tab[i + NB_Columns] == 0) 
  {
    tab[i] = 0;
    tab[i + NB_Columns] = player;
    print_grid(tab);
    sleep(1);
    i += NB_Columns;
  }
  moove_piece->x = i / NB_Columns;
  return *moove_piece;
}


int sub_check(int *tab, int x, int y, int player, int r, int c) {
  x += r;
  y += c;
  if (x * NB_Columns + y >= 0 && x * NB_Columns + y <= NB_Columns * NB_Rows &&
      tab[x * NB_Columns + y] == player) {
    return sub_check(tab, x, y, player, r, c) + 1;
  }
  return 0;
}

bool check(int *tab, int x, int y, int r, int c) {
  int p = tab[x * NB_Columns + y];
  if (p == 0)
    perror("Bad placement, player == 0. Can't be possible\n");
  int score1 = sub_check(tab, x, y, p, r, c);
  int score2 = sub_check(tab, x, y, p, -r, -c);
  return score1 + score2 + 1 >= 4;
}


int main() {
  int* tab =  (int*)calloc(NB_Rows * NB_Columns, sizeof(int));
  bool end = false;
  struct coo *last = (struct coo *)malloc(sizeof(struct coo));
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\033[1A");
  int player = 1;
  int cursor = 0;
  print_grid(tab);
  print_cursor(cursor);


  while (end != true) {
    // possible solution -> char input = getch();
    char input = getch();
    if (input_handeler(input, &cursor))
    {
      *last = update_grid(tab, player, cursor);
      end = check(tab, last->x, last->y, 1, -1) ||
          check(tab, last->x, last->y, 1, 1) ||
          check(tab, last->x, last->y, 1, 0) ||
          check(tab, last->x, last->y, 0, 1); 
      player *= -1;
    }
    //*last = moove(tab, player);
    print_grid(tab);
    print_cursor(cursor);
  }

  // printf("[CLIENT]:helle world!\n");

  // Print Bravo !
  printf("\n\n  ____                         _ \n |  _ \\                      "
         " | |\n | |_) |_ __ __ ___   _____   | |\n |  _ <| '__/ _` \\ \\ / / "
         "_ \\  | |\n | |_) | | | (_| |\\ V / (_) | |_|\n |____/|_|  \\__,_| "
         "\\_/ \\___/  (_)\n\n");

  free(tab);
}
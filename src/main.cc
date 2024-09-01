#define NB_strat 3
/* gamerules */
#define BDG_INIT 3
#define BDG_ROUD 1

// #include "Board_managment.hh"
#include "Automaton.hh"
#include "Stratagems.hh"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <thread>

/* stack */

struct stack{
  int bmap;
  int *durations;
  void (*functions[8])(int *tab);
};

int *to_binary(int x)
{
  int *res = (int *)calloc(8, sizeof(int));
  char test[8];
  sprintf(test, "%8.b", x);
  for (int i = 0; i< 8; i++)
  {
    res[7-i]=test[i]=='1';
  }
  return res;
}

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

void print_canvas()
{
  // \033[0;33m  \033[0m
  char canevas[] = "\r\
                                                    ╭═══════╮\n\
                       ┌────────────────────────────║       ║────────────────────────────┐\n\
  \033[0;33m╔═════════════════════\033[0m╲___________________________║ ▄   ▄ ║___________________________╱\033[0;33m═════════════════════╗\n\    
  \033[0;33m║                         \033[0m╲_______________________╰─╮ ▴ ╭─╯_______________________╱                         \033[0;33m║\n\
  \033[0;33m║                                   \033[0m╲______ ╲_______╰─═─╯_____╱ ______╱                                     \033[0;33m║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m║                                       ║                                                                   ║\n\
  \033[0;33m╚═════════════════════════════════════╦═╩══════════════════════════════╦════════════════════════════════════╝\033[0;0m\n\
  \033[0;33m                                      ║      \033[0mshow stratagèmes : P\033[0;33m      ║\033[0;0m\n\
  \033[0;33m                                      ╚════════════════════════════════╝\033[0;0m\033[2A\n";
  
  printf("%s",canevas);
}

void print_message()
{
  char message[] = "\r\e[43C\e[17A  \033[0mGreetings \033[0;33mHelldivers\033[0m,                                            \e[67D\e[1B\
  \033[0mProve you have the strength and courage to protect the \033[0;34mliberty\033[0m   \e[67D\e[1B\
  \033[0magainst the most vicious and cunning threats of the \033[0;34mdemocratie\033[0m.  \e[67D\e[1B\
                                                                   \e[67D\e[1B\
  \033[0mBeat this \033[0;31mautomaton\033[0m strategist at the SuperConect4 to prove the  \e[67D\e[1B\
  \033[0msuperiority of the lasy \033[0;34mliberty\033[0m. Do not show merci to this       \e[67D\e[1B\
  \033[0minsensitive \033[0;31mfoe\033[0m of the super earth. Wins victory over this       \033[0;33m║\033[0m\e[68D\e[1B\
  \033[0menemy and proclaims the superiotity of \033[0;34mmanaged democracy\033[0m.        \e[67D\e[1B\
                                                                   \e[67D\e[1B\
  \033[0mThis is a \033[0;34mMANDATORY\033[0m training from \033[0;34mministry of Intelligence\033[0m.      \e[67D\e[1B\
  \033[0mEvery attempt to avoid this training session will result in      \e[67D\e[1B\
  \033[0ma suspension of the helldivers armed corps and an audience with  \e[67D\e[1B\
  \033[0mthe \033[0;34mministry of Humanity\033[0;0m.                                        \e[67D\e[1B\
                                                                   \e[67D\e[1B\
  \033[0;34mFOR SUPER EARTH!\033[0;0m                                                 \e[67D\e[1B\
                                                                \e[67D\e[1B\
\e[44C\033[0;33m═\033[0m\e[1B\r";                                                                                    
  printf("%s", message);
}

void print_strat_arrows(struct stratagem strat, bool avia)
{

  for(int i = 0; i<strat.total_size; i++)
  {
    if (avia)
    {
      if (strat.current > i)
      {
        printf("\033[0;33m");
      }
      else
      {
        printf("\033[1;0m");
      }
    }
    else
    {
      printf("\033[90m");
    }
    switch (strat.buffer[i])
    {
    case 1:
      printf("↑");
      break;
    case 2:
      printf("↓");
      break;
    case 3:
      printf("→");
      break;
    case 4:
      printf("←");
      break;
    
    default:
      break;
    }
    printf("\033[0m");
  }
  printf("\033[%dD",strat.total_size);
  //printf("%s■", (avia?"\033[0;33m":"\033[0m"), "\033[0m");
}

void print_strat(struct stratagem strat, bool avia, int budget)
{
  char *color = "\033[0;34m";
  char *color_name = "\033[0;33m";
  if (strat.cost>budget)
  {
    color = "\033[0;31m"; 
  }
  if (!avia)
  {
    color_name = "\033[90m";
    color = "\033[90m";
  }
  printf("%s%s\033[0m\r\033[85C\033[16C%s    %dR\033[0m\033[1B\r\033[86C  ",color_name, strat.name, color, strat.cost);
  print_strat_arrows(strat, avia);
  if (strat.in_reload)
  {
    printf("\033[8C\033[90mRELOAD[%d] %d\033[0m", (strat.reload), strat.charges);
  }
  else
  {
    printf("\033[18C%d\033[0m", strat.charges);
  }
  //printf("%d\033[0m", strat.charges);
  fflush(stdout);
}

void print_stratagems(struct stratagem *stratagems[], bool avia[], int budget, bool stratagem)
{
  // ↑↓→←  mine:  ↓←↑→  500Kg:
  char message[] = "\r\e[45C\e[17AUse the Super Erath arsenal to establish the our superiority.    \e[67D\e[1B\
                                                                   \e[67D\e[1B\
  Using these highly democratic weapons will cost you budget       \e[67D\e[1B\
  points. You will get more budget point every turn.               \e[67D\e[1B\
  Some stratagem need time to be reload, so when you use all       \e[67D\e[1B\
  charge available you have to wait before                         \e[67D\e[1B\
  reuse them.                            \033[0;33m╔═════════════════════════╣\033[0m\e[68D\e[1B\
                             \033[0;33m┌──────┐    ║\033[0m                         \e[67D\e[1B\
                             \033[0;33m│    R │    ║\033[0m                         \e[67D\e[1B\
                             \033[0;33m└──────┘    ║\033[0m                         \e[67D\e[1B\
  Stratagems mode :                      \033[0;33m║\033[0m                         \e[67D\e[1B\
                                         \033[0;33m║\033[0m                         \e[67D\e[1B\
                                         \033[0;33m║\033[0m                         \e[67D\e[1B\ 
                                         \033[0;33m║\033[0m                         \e[67D\e[1B\
                                         \033[0;33m║\033[0m                         \e[67D\e[1B\
                                         \033[0;33m║\033[0m                         \e[67D\e[1B\
\e[41C\033[0;33m╩\033[0m\e[1B\r";
/* [----name-----]   XR /  ↓←↑→↓↓↓ RELOAD[X] 0*/
  printf("%s", message);
  fflush(stdout);
  printf("\033[11A");
  /*budget*/
  printf("\033[0;33m\r\033[2B\033[%dC%d\r\033[0m", 76-(budget>9? 1 : 0)-(budget>99?1:0), budget);
  /*stratagem mode*/
  printf("\r\033[63C\033[2B%s\r\033[2A", stratagem? "\033[0;33mENABLE\033[0m" : "DISABLE");
  /*stratagems*/
  for (int i =0; i< NB_strat; i++)
  {
    printf("\r\033[87C");
    print_strat(*stratagems[i], avia[i], budget);
    printf("\033[1B");
  }
  printf("\033[%dB", 9-NB_strat*2);
}

void print_congrats(bool player_has_won)
{
  printf("\033[45C\033[17A");
  char congrats[] = "Good job \033[0;33mhelldiver\033[0;0m,                                              \033[67D\033[1B\
  Beating this enemy of democracy is a proof of your strength and  \033[67D\033[1B\
  your \033[0;34mdevotion\033[0;0m for the \033[0;34mSuper earth\033[0;0m. You are the pride of the      \033[67D\033[1B\
  \033[0;34mSuper Earth\033[0;0m.                                                     \033[67D\033[1B\
                                                                   \033[67D\033[1B\
  You just have proved that helldiver are superior none only on    \033[67D\033[1B\
  the battlefield but also by their strategy.                      \033[0;33m║\033[0m\033[68D\033[1B\
  You are the best super earth could hope for.                     \033[67D\033[1B\
                                                                   \033[67D\033[1B\
  This test is the first of a series. The goal of these training   \033[67D\033[1B\
  is to determine best helldivers for a future special mission.    \033[67D\033[1B\
  These tests are the property of the \033[0;34mministry of Intelligence\033[0;0m.    \033[67D\033[1B\
  No distribution of these tests will tolerated.                   \033[67D\033[1B\
                                                                   \033[67D\033[1B\
  Keep going helldiver, \033[0;34mfor super earth!\033[0;0m                           \033[67D\033[1B\
                                                                   \033[67D\033[1B";
  char regrets[] = "Well, i \033[0;31mwarnd\033[0;0m you.                                               \033[67D\033[1B\
  you have been relieved of your duties. until now you are not a   \033[67D\033[1B\
  helldiver anymore. you have to join Mars as soon as possible.    \033[67D\033[1B\
  All your weapons will be reassigned to new helldiver.            \033[67D\033[1B\
  Your cape will be taken away from you, you do not deserve it.    \033[67D\033[1B\
  Not anymore.                                                     \033[67D\033[1B\
                                                                   \033[0;33m║\033[0m\033[68D\033[1B\
  You are the shame of Super earth.                                \033[67D\033[1B\
  You will recive a transmition from the ministry of Humanity.     \033[67D\033[1B\
  You are accused of \033[0;31mbond\033[0;0m with the enemy, \033[0;31mconspiracy\033[0;0m against       \033[67D\033[1B\
  super earth and act of \033[0;31mtreachery\033[0;0m. \033[0;31mTraitor\033[0;0m does not deserve       \033[67D\033[1B\
  defence. The Ministry of Science will try to make your body      \033[67D\033[1B\
  usefull for the super earth.                                     \033[67D\033[1B\
                                                                   \033[67D\033[1B\
  You chosed the wrong side. \033[0;31mgoodbye traitor\033[0;0m                       \033[67D\033[1B\
                                                                   \033[67D\033[1B";
  printf("%s",player_has_won?congrats:regrets);
  printf("\033[41C\033[0;33m═\033[0m\033[1B");
  //printf("\033[2B\r");
}

void print_cursor(int cursor)
{
  printf("\033[19A \n\t");
  printf("\033[%dC", (1+4*cursor));
  printf("┌─┐\033[1B\033[3D│ │\033[1B\033[3D╲_/\033[16B\r");
}

/* update the {cursor} with user input and return True id the input is validate*/
bool input_handeler(char input, int *cursor, bool *strat, bool *strat_inp)// int inputs[6])
{
  bool res = false;
  switch (input)
  {
  case 'd':
    *cursor += (*cursor < 6)? 1:0;
    break;
  case 'a':
  case 'q':
    *cursor -= (*cursor > 0)? 1:0;
    break;
  case 's':
    res = true;
    break;
  case 'p':
    *strat = !(*strat);
    break;
  case 'e':
    *strat_inp = !(*strat_inp) && *strat;
    break;
  default:
    break;
  }
  return res;
}

int strat_handeler(char input, bool *strat_disp, bool *strat_inp)
{
  int res = 0;
  switch (input)
  {
  case 'w':
  case 'z':
    res = 1;
    break;
  case 's':
    res = 2;
    break;
  case 'd':
    res = 3;
    break;
  case 'q':
  case 'a':
    res = 4;
    break;
  case 'p':
    *strat_disp = !(*strat_disp);
    break;
  case 'e':
    *strat_inp = !(*strat_inp) && *strat_disp;
    break;
  default:
  break;
  }
  return res;
}

/* return -1 if none stratagmes is ready */
int strat_maker(struct stratagem *stratagems[], bool availability[], int sta_input, int budget)
{
  bool one_on = false;
  for(int i = 0; i < NB_strat;i++)
  {
    if (!availability[i])
    {
      continue;
    }
    struct stratagem *stratagem = stratagems[i];
    if (stratagem->buffer[stratagem->current] == sta_input)
    {
      stratagem->current++;
      one_on = true;
    }
    else
    {
      stratagem->current = 0;
      availability[i] = false;
    }
    if (stratagem->current == stratagem->total_size)
    {
      for(int i = 0; i < NB_strat;i++)
      {
        struct stratagem *stratagem = stratagems[i];
        stratagem->current = 0;
        availability[i] = stratagem->cost <= budget;
      }
      return i;
    }
  }
  /* reset */
  if (!one_on)
  {
    for(int i = 0; i < NB_strat;i++)
    {
      struct stratagem *stratagem = stratagems[i];
      stratagem->current = 0;
      availability[i] = stratagem-> cost <= budget;
    }
  }
  return -1;
}

void check_availability(bool avia[4], struct stratagem *stratagems[4], int budget)
{
  for (int i = 0; i< NB_strat; i++)
  {
    avia[i] = stratagems[i]->cost <= budget && stratagems[i]->charges > 0;
  }
}

int main()
{
  int* tab =  (int*)calloc(NB_Rows * NB_Columns, sizeof(int));
  bool end = false;
  struct coo *last = (struct coo *)calloc(1, sizeof(struct coo));
  int player = -1;
  int cursor = 0;
  bool strat_page = false;
  bool strat_input = false;
  int budget = BDG_INIT ;

  struct stratagem b500k = {5, 0, {1,3,2,2,2,0,0}, 3, 2, 2, 3, 0, false, false, strat_fun_500k, "500Kg bomb", false, -1,0};
  struct stratagem mine  = {4, 0, {2,4,1,3,0,0,0}, 1, 1, 1, 1, 0, false, false, strat_fun_mine, "mine", false, -1, 0};
  struct stratagem barrage = {6, 0, {3,3,2,4,3,2,0}, 8, 1, 1, 5, 0, false, false, strat_fun_barrage, "380mm barrage", true, 0, 3};

  struct stratagem *stratagems[4] = {&b500k, &mine, &barrage, 0};
  bool availability[4] = {true, true, true, true};

  int rout_bitmap = 0;
  int *rout_durations = (int*)calloc(8, sizeof(int));
  void (*rout_functions[8])(int *tab) = {&strat_rout_barrage, 0, 0, 0, 0, 0, 0, 0};

  print_canvas();
  print_message();
  print_grid(tab);
  print_cursor(cursor);

  printf("\e[?25l");
  while (end != true) {
    if (player == 1) /* player turn */
    {
      char input = getch();

      if (!strat_input)
      {
        if (input_handeler(input, &cursor, &strat_page, &strat_input))
        {
          if (colomn_is_full(tab,cursor))
          {
            continue;
          }
          if (update_grid(tab, player, cursor, last))
          {
            end = game_finished(tab, last->x, last->y);
          }
          player *= -1;
          reload_all(stratagems,NB_strat);
          /* routine check */
          if (rout_bitmap != 0)
          {
            int *ids = to_binary(rout_bitmap);
            for (int id = 0; id<8; id++)
            {
              if (ids[id])
              {
                rout_functions[id](tab);
                if (rout_durations[id]>1)
                {
                  rout_durations[id]--;
                }
                else
                {
                  rout_bitmap -= id +1;
                }
              }
            }
            free(ids);
          }
          budget += BDG_ROUD;
        }
      }
      else
      {
        int code = strat_handeler(input, &strat_page, &strat_input);
        check_availability(availability, stratagems, budget);
        int strat_id = strat_maker(stratagems, availability, code, budget);
        print_stratagems(stratagems, availability, budget, strat_input);
        if (strat_id!=-1)
        {
          stratagems[strat_id]->function(tab, cursor);
          stratagems[strat_id]->charges--;
          if (stratagems[strat_id]->got_rout)
          {
            rout_durations[stratagems[strat_id]->rout_id] = stratagems[strat_id]->rout_duration;
            rout_bitmap += stratagems[strat_id]->rout_id+1;
          }
          strat_input = false;
          budget-=stratagems[strat_id]->cost;
        }
      }
    }
    else /* AI turn */
    {
      int col = automaton_thought_maker(tab, 6);
      //printf("automaton play -> %d\n", col);
      if (update_grid(tab, player, col, last))
      {
        end = game_finished(tab, last->x, last->y);
      }

      player *= -1;
    }
    
    print_grid(tab);
    check_availability(availability, stratagems, budget);
    (strat_page)? print_stratagems(stratagems, availability, budget, strat_input) : print_message();
    print_cursor(cursor);
  }
  if (player == -1)
    print_congrats(true);
  else
    print_congrats(false);
  print_grid(tab);
  printf("\e[?25h\e[1B\n");
  fflush(stdout);
  free(tab);
  free(last);
}
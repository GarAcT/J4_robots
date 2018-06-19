#include <stdio.h>

#define HEIGHT 21
#define WIDTH  63

void init_stage(int *stage);
void clear_stage(int *stage);

void disp_stage(int *stage);
void print_horizontal_frame(int length);

int main(void)
{
  int stage[HEIGHT*WIDTH];

  init_stage(stage);

  disp_stage(stage);
}

void init_stage(int *stage)
{
  int player_x, player_y;

  clear_stage(stage);

  player_y = HEIGHT/2;
  player_x = WIDTH/2;
  stage[player_y*WIDTH + player_x] = 1;

}

void clear_stage(int *stage)
{
  int i;

  for(i = 0; i < HEIGHT*WIDTH; i++){
    stage[i] = 0;
  }
}

void disp_stage(int *stage)
{
  int x,y;

  print_horizontal_frame(WIDTH);
  for(y = 0; y < HEIGHT; y++){
    printf("|");
    for(x = 0; x < WIDTH; x++){
      switch(stage[y*WIDTH + x]){
        case 0:
          printf(" ");
          break;
        case 1:
          printf("@");
          break;
        default:
          printf("%d", stage[y*WIDTH + x]);
          break;
      }
    }
    printf("|\n");
  }
  print_horizontal_frame(WIDTH);
}

void print_horizontal_frame(int length)
{
  int i;

  printf("+");
  for(i = 0; i < length; i++){
    printf("-");
  }
  printf("+\n");
}

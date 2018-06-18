#include <stdio.h>

#define HEIGHT 21
#define WIDTH  63

void clear_stage(int *stage);
void disp_stage(int *stage);
void print_horizontal_frame(int length);

int main(void)
{
  int stage[HEIGHT*WIDTH];

  clear_stage(stage);

  disp_stage(stage);
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

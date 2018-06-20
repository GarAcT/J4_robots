#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 21
#define WIDTH  63
#define MAX_ENEMY (HEIGHT*WIDTH / 3)

#define MIN(x,y) ((x<y) ? x : y)


typedef struct NODE {
  struct NODE *prev;
  struct NODE *next;

  int entity_id;
  int x;
  int y;
} entity_t;


void clear_stage(int *stage);
entity_t *init_entity(int enemy_num);

void disp_stage(int *stage);
void print_horizontal_frame(int length);

void shuffle(int *array);

entity_t *new_entity_list();
void add_entity(entity_t *list, int pos, int id);

void show_entity(entity_t *list);


int main(void)
{
  int stage[HEIGHT*WIDTH];
  entity_t *entity_list;

  clear_stage(stage);
  entity_list = init_entity(5);

  disp_stage(stage);

  show_entity(entity_list);
}


void clear_stage(int *stage)
{
  int i;

  for(i = 0; i < HEIGHT*WIDTH; i++){
    stage[i] = 0;
  }
}

entity_t *init_entity(int enemy_num)
{
  int i;
  int array[HEIGHT*WIDTH];
  entity_t *list;

  for(i = 0; i < HEIGHT*WIDTH; i++){
    array[i] = i;
  }
  shuffle(array);

  list = new_entity_list();
  list->x = array[0] % WIDTH;
  list->y = array[0] / WIDTH;
  for(i = 1; i <= enemy_num; i++){
    add_entity(list, array[i], 2);
  }

  return list;
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
        case 2:
          printf("+");
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


void shuffle(int *array)
{
  int i,j;
  int tmp;

  srand((unsigned)time(NULL));

  for(i = 0; i < HEIGHT*WIDTH; i++){
    j = rand()%(HEIGHT*WIDTH);
    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }
}


entity_t *new_entity_list()
{
  entity_t *head = (entity_t *)malloc(sizeof(entity_t));

  head->prev = NULL;
  head->next = (entity_t *)malloc(sizeof(entity_t));
  head->entity_id = 1;  // 双方向リストの操作を簡略化するため両端にダミーが必要だが、Entityの中ではプレイヤー数は絶対に1つ（もしくは1つ以上）なので、先頭をプレイヤーノードにする
  head->x = -1;
  head->y = -1; // プレイヤーの位置が定義されていないことを明示するために-1で示す

  head->next->prev = head;
  head->next->next = NULL;
  head->next->entity_id = 0; // 終端ノード

  return head;
}

void add_entity(entity_t *list, int pos, int id)
{
  entity_t *node = (entity_t *)malloc(sizeof(entity_t));

  node->x = pos % WIDTH;
  node->y = pos / WIDTH;
  node->entity_id = id;
  node->prev = list;
  node->next = list->next;

  node->prev->next = node;
  node->next->prev = node;
}

void show_entity(entity_t *list)
{
  entity_t *p;
  int i;

  p = list;
  i = 0;
  while(p != NULL){
    printf("[node-%d]:\n", i);
    printf("  entity ID: %d\n", p->entity_id);
    printf("  x: %d\n", p->x);
    printf("  y: %d\n", p->y);
    printf("\n");

    p = p->next;
    i++;
  }
}

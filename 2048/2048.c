// Libraies
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Contants
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
#define NO_MOVE 0

#define BOARD_VOID 0

#define SIZE 4

// Structures
struct new_value {
  int x,y;
};

// Functions Headers
void init_game();
void print_game();
void end_game();
void create_value();
void set_direction();
void move_numbers();
void move_up();
void move_down();
void move_left();
void move_right();

// GLOBAL VARIABLES
int game_over = 0;
int direction = 0;
char movement;
struct new_value new_value;

// Initialyze Map
int board[SIZE][SIZE] = {0};

int main() {
  init_game();

  while (!game_over) { 

    movement = getchar();
    while (getchar() != '\n'); // Clean buffer
    
    set_direction();
    move_numbers();

    create_value();
    print_game();
  }

  end_game();

  return 0;
}

void init_game() {
  srand(time(NULL));
  create_value();
  print_game();  
}

void print_game() {

  // Clean Console
  printf("\e[1;1H\e[2J");

  // Print Map
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%d   ", board[i][j]);
    }
    printf("\n\n\r");
  }
  printf("\n\n\r");
}

void end_game() {

  sleep(1);

  // Clean Console
  printf("\e[1;1H\e[2J");

  printf("\n\n\t\tGAME OVER\t\t\n\n");

  sleep(1);

}

void create_value() {

  int valid_positions = 0;

  for (int i = 0; i < SIZE; i++) 
    for (int j = 0; j < SIZE; j++) 
      if (board[i][j] == 0)
        valid_positions++;

  if (valid_positions == 0) {
    game_over = 1;
    return;
  }

  do {
    new_value.x = rand() % SIZE; 
    new_value.y = rand() % SIZE; 
  } while ( board[new_value.x][new_value.y] != BOARD_VOID);

  board[new_value.x][new_value.y] = board[new_value.x][new_value.y] + 1;
  
}

void set_direction() {
  // if ( dvorak or qwerty )
  if ( (movement == ',') || (movement == 'w') ) {
    direction = UP;
  } else if ( (movement == 'o') || (movement == 's') ) {
    direction = DOWN;
  } else if ( (movement == 'a') || (movement == 'a') ) {
    direction = LEFT;
  } else if ( (movement == 'e') || (movement == 'd') ) {
    direction = RIGHT;
  } else {
    direction = NO_MOVE;
  }
}

void move_numbers() {

  if (direction == UP) {
    move_up();
  } else if (direction == DOWN) {
    move_down();
  } else if (direction == LEFT) {
    move_left();
  } else if (direction == RIGHT) {
    move_right();
  }

}

void move_up() {
  // travel board
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // search numbers to move
      if ((board[i][j] != BOARD_VOID) && (i != 0)) {
        // number to move
        for (int k = 0; k < i; k++) {
          // empty position (valid movement)
          if (board[i-1-k][j] == BOARD_VOID) {
            board[i-1-k][j] = board[i-k][j];
            board[i-k][j] = BOARD_VOID;
          }
          // update value
          if (board[i-1-k][j] == board[i-k][j]) {
            board[i-1-k][j] = board[i-k][j] + 1;
            board[i-k][j] = BOARD_VOID;
            break;
          }
        }
      }
    }
  }
}

void move_down() {
  // travel board
  for (int i = SIZE - 1; i >= 0; i--) {
    for (int j = 0; j < SIZE; j++) {
      // search numbers to move
      if ((board[i][j] != BOARD_VOID) && (i != SIZE - 1)) {
        // number to move
        for (int k = 0; k < SIZE - i - 1; k++) {
          // empty position (valid movement)
          if (board[i+1+k][j] == BOARD_VOID) {
            board[i+1+k][j] = board[i+k][j];
            board[i+k][j] = BOARD_VOID;
          }
          // update value
          if (board[i+1+k][j] == board[i+k][j]) {
            board[i+1+k][j] = board[i+k][j] + 1;
            board[i+k][j] = BOARD_VOID;
            break;
          }
        }
      }
    }
  }
}

void move_left() {
  // travel board
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // search numbers to move
      if ((board[i][j] != BOARD_VOID) && (j != 0)) {
        // number to move
        for (int k = 0; k < j; k++) {
          // empty position (valid movement)
          if (board[i][j-1-k] == BOARD_VOID) {
            board[i][j-1-k] = board[i][j-k];
            board[i][j-k] = BOARD_VOID;
          }
          // update value
          if (board[i][j-1-k] == board[i][j-k]) {
            board[i][j-1-k] = board[i][j-k] + 1;
            board[i][j-k] = BOARD_VOID;
            break;
          }
        }
      }
    }
  }
}

void move_right() {
  // travel board
  for (int i = 0; i < SIZE; i++) {
    for (int j = SIZE - 1; j >= 0; j--) {
      // search numbers to move
      if ((board[i][j] != BOARD_VOID) && (j != SIZE - 1)) {
        // number to move
        for (int k = 0; k < SIZE - j - 1; k++) {
          // empty position (valid movement)
          if (board[i][j+1+k] == BOARD_VOID) {
            board[i][j+1+k] = board[i][j+k];
            board[i][j+k] = BOARD_VOID;
          }
          // update value
          if (board[i][j+1+k] == board[i][j+k]) {
            board[i][j+1+k] = board[i][j+k] + 1;
            board[i][j+k] = BOARD_VOID;
            break;
          }
        }
      }
    }
  }
}

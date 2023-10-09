#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Contantes
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

// Grafics
#define MAP_VOID 0
#define MAP_WALL 1
#define MAP_SNAKE 2
#define MAP_FOOD 3
#define MAP_DEAD 4

#define SIZE 20
//#define fps 10

// structures
struct pose {
    int x,y;
};

struct food {
    int x,y;
};

// Functions Headers
void init_game();
void print_game();
void generate_food();
void calculate_pose();
void configure_map();
void validate_position();
void eat_food();
void end_game();
void print_end_game();

// GLOBAL VARIABLES
int direction = DOWN;
int game_over = 0;
struct food food;
// Time Between frames (Microseconds)
int fps = 0;
//float time_sleep = 1000000.0 / fps;

// Initialyze Map
int map[SIZE][SIZE] = {0};

// Initializy Player
struct pose snake[SIZE*SIZE] = {0};
struct pose previousPose;

int main() {
    init_game();

    print_game();

    float time_sleep = 1000000.0 / fps;

    int ch;
    while (!game_over) {
        // Esperar a que el usuario presione una tecla
        ch = getch();

        print_game();

        // Verificar si la tecla presionada es una de las flechas
        if ((ch == KEY_UP) || (ch == ',') || (ch == ',')) {
            if ( ! ( direction == DOWN ) )
                direction = UP;
        } else if ((ch == KEY_DOWN) || (ch == 'o') || (ch == 'O')) {
            if ( ! ( direction == UP )
  )               direction = DOWN;
        } else if ((ch == KEY_LEFT) || (ch == 'a') || (ch == 'A')) {
            if ( ! ( direction == RIGHT  ))
                direction = LEFT;
        } else if ((ch == KEY_RIGHT) || (ch == 'e') || (ch == 'E')) {
            if ( ! ( direction == LEFT ) )
                direction = RIGHT;
        } else if (ch == 27) {
            // Tecla Esc (27 es el código de escape)
            break; // Salir del bucle si se presiona Esc
        }
        
        calculate_pose();

        validate_position();

        //sleep(1);
        usleep(time_sleep);
        //refresh(); // Actualizar la pantalla


    }

    // Finalizar la biblioteca ncurses
    endwin();

    print_end_game();
  
    end_game();

    return 0;
}

void init_game() {
    srand(time(NULL));

    printf("[+] Ingrese FPS (12): ");
    scanf("%d", &fps);

    initscr();               // Initialyze lib ncurses
    noecho();                // Dont show character
    curs_set(0);             // Hide cursor
    keypad(stdscr, TRUE);    // Read special caracters (arrows)
    nodelay(stdscr, TRUE);   // Dont wait for input
    timeout(0);              // Dont stop the code

    // MAP
    // Walls
    for (int i = 0; i < SIZE; i++) {
        map[0][i] = 1;
        map[SIZE - 1][i] = 1;
        map[i][0] = 1;
        map[i][SIZE -1] = 1;
    } 

    // Clean Map 
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            map[i][j] = 0;
        }
    }

    // Player
    snake[0].x = 1;
    snake[0].y = 1;

    // Generar comida
    generate_food();
}

void configure_map() {
    // Walls
    for (int i = 0; i < SIZE; i++) {
        map[0][i] = MAP_WALL;
        map[SIZE - 1][i] = MAP_WALL;
        map[i][0] = MAP_WALL;
        map[i][SIZE -1] = MAP_WALL;
    } 

    // Clean Map 
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            map[i][j] = MAP_VOID;
        }
    }

    // Food
    map[food.x][food.y] = MAP_FOOD;

}

void print_game() {

    configure_map();

    // Configure snake in map
    for (int i = 0; i < SIZE * SIZE; i++) {
        if (snake[i].x == 0 && snake[i].y == 0) {
            // posicion invalida
            break;
        }
        map[snake[i].x][snake[i].y] = MAP_SNAKE;
    }

    // Clean Console
    printf("\e[1;1H\e[2J");

    // Print Map
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ( map[i][j] == MAP_VOID ) {
                printf("  "); // void
            } else if ( map[i][j] == MAP_WALL) {
                printf("+ "); // wall
            } else if ( map[i][j] == MAP_SNAKE) {
                printf("O "); // snake
            } else if ( map[i][j] == MAP_FOOD) {
                printf("Ø "); // food
            } else if ( map[i][j] == MAP_DEAD) {
                printf("X "); // dead snake
            } else {
                printf("! "); // Error
            }
        }
        printf("\n\r");
    }
    printf("\n\r");
}

void generate_food() {
    do {
        food.x = rand() % (SIZE - 2) + 1;
        food.y = rand() % (SIZE - 2) + 1;
    } while (map[food.x][food.y] != MAP_VOID);
    map[food.x][food.y] = MAP_FOOD;
}

void eat_food() {

    int i;
    for ( i = 1; i < SIZE * SIZE; i++) {
        if (snake[i].x == 0) {
            // posicion invalida
            snake[i].x = food.x;
            snake[i].y = food.y;
            break;
        }
    }

    generate_food();

}

void calculate_pose() {

    if (( snake[0].x == food.x ) && ( snake[0].y == food.y )) {
        eat_food();
    } 

    previousPose = snake[0];
    struct pose aux;

    switch (direction) {
        case UP:
            snake[0].x--;
            break;
        case DOWN:
            snake[0].x++;
            break;
        case LEFT:
            snake[0].y--;
            break;
        case RIGHT:
            snake[0].y++;
            break;
        default:
            // TODO error
            printf("[!] ERROR. Direccion desconocida.");
            break;
    }


    for (int i = 1; i < SIZE * SIZE; i++) {
        if (snake[i].x == 0) {
            // posicion invalida
            break;
        }
        aux = snake[i];
        snake[i] = previousPose;
        previousPose = aux;
    }
    
}

void validate_position() {

    if ( snake[0].x == 0 || snake[0].y == 0  || snake[0].x == SIZE - 1 || snake[0].y == SIZE - 1 ) {
        game_over = 1;
    }

    for (int i = 1; i < SIZE * SIZE; i++) {
        if (snake[i].x == 0) {
            // posicion invalida
            break;
        }
        if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) {
            game_over = 1;
            break;
        } 
    }

}

void end_game() {

  sleep(1);

  // Clean Console
  printf("\e[1;1H\e[2J");

  printf("\n\n\t\tGAME OVER\t\t\n\n");

  sleep(1);

}


void print_end_game() {

  configure_map();

  float time_sleep = 1000000.0 / fps;
    
  // Configure snake in map
  for (int i = 0; i < SIZE * SIZE; i++) {
    if (snake[i].x == 0 && snake[i].y == 0) {
      // posicion invalida
      break;
    }

    map[snake[i].x][snake[i].y] = MAP_DEAD;

    // Clean Console
    printf("\e[1;1H\e[2J");

    // Print Map
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if ( map[i][j] == MAP_VOID ) {
          printf("  "); // void
        } else if ( map[i][j] == MAP_WALL) {
          printf("+ "); // wall
        } else if ( map[i][j] == MAP_SNAKE) {
          printf("O "); // snake
        } else if ( map[i][j] == MAP_FOOD) {
          printf("Ø "); // food
        } else if ( map[i][j] == MAP_DEAD) {
          printf("X "); // dead snake
        } else {
          printf("! "); // Error
        }
      }
      printf("\n\r");
    }
    printf("\n\r");
    usleep(time_sleep);

  }

  sleep(1);

}

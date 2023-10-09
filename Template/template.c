// Libraies
#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Contants
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

// Grafics
// Constants to store as value to print the game
#define MAP_VOID 0
#define MAP_WALL 1
#define MAP_SNAKE 2
#define MAP_FOOD 3
#define MAP_DEAD 4

#define SIZE 20

// Structures
struct pose {
  int x,y;
};

// Functions Headers
void init_game();
void print_game();
void end_game();

// GLOBAL VARIABLES
int game_over = 0;
int fps = 0;

// Initialyze Map

// Initialize Player

int main() {
    init_game();
    print_game();
    float sleep_microseconds = 1000000.0 / fps;

    while (!game_over) {
      gameLoop();
    }

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

    // Configure Map

    // Configure Player
  
}

void print_game() {

    configure_map();

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

void end_game() {

  sleep(1);

  // Finalizar la biblioteca ncurses
  endwin();

  // Clean Console
  printf("\e[1;1H\e[2J");

  printf("\n\n\t\tGAME OVER\t\t\n\n");

  sleep(1);

}


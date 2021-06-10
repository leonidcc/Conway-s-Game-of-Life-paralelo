#include "board.h"

/******************************************************************************/
/* Representamos las células vivas como 'O' y las muertas como 'X' */
#define ALIVE 'O'
#define DEAD  'X'
/******************************************************************************/
/* La estructura de un juego es simplemente un tablero y la cantidad de veces
que se va a iterar */
struct _game {
  board_t *board;
  unsigned int cycles;
};

typedef struct _game game_t;
/******************************************************************************/

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename);

/* Simulamos el Juego de la Vida de Conway con tablero 'board' la cantidad de
ciclos indicados en 'cycles' en 'nuprocs' unidades de procesamiento*/
board_t *congwayGoL(board_t *board, unsigned int cycles, const int nuproc);

/* Guardamos el tablero 'board' en el archivo 'filename' */
void writeBoard(game_t *game, const char *filename);

// calcula los vecinos vivos de una célula
int cantvecinas(board_t *board, int i);

// actualiza la celula dependiendo de la cantidad de vecinos vivos que tiene
void* update_particion(void *dato);

// actualiza el tablero con la nueva generación
void update(board_t *board, const int Nhilos);

// setea las celulas por 0 y 1
int board_init_def(board_t *board);

void game_destroy(game_t *game);

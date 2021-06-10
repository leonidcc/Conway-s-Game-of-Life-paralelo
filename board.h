#ifndef BOARD
#define BOARD

#include <stdlib.h>

/******************************************************************************/
/* Definición de la estructura de datos del tablero */

struct _board{
  char* tablero;
  int col;
  int row;
};
typedef struct _board board_t;
/******************************************************************************/
/******************************************************************************/

/* Funciones sobre el tablero */

/* Creación del tablero */
int board_init(board_t *board, int col, int row);

/* Leer de una lista de caracteres e interpretarla como un tablero */
int board_load(board_t *board, char *str);

/* Destroy board */
void board_destroy(board_t *board);

#endif

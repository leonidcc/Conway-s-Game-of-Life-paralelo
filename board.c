#include "board.h"
#include <string.h>

int board_init(board_t *board, int col, int row){
  board->tablero = malloc(sizeof(char) * (row*col));
  board->col = col;
  board->row = row;

  return 1;
}

int board_load(board_t *board, char *str){
  memcpy(board->tablero,str,sizeof(char)*(board->col*board->row));
  return 1;
}

void board_destroy(board_t *board){
  free(board->tablero);
  free(board);
}
 

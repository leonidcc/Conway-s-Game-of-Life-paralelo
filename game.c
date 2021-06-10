#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "board.h"
#include "game.h"

// DEFININICIONES GLOBALES
board_t *actual;
char *temp;

// setea las celulas por 0 y 1
int board_init_def(board_t *board){
  int tam = board->row * board->col;
  for (int i = 0; i < tam; i++) {
    if(board->tablero[i] == ALIVE ) board->tablero[i] = '\1';
    else board->tablero[i] = '\0';
  }

}

game_t* loadGame(const char *filename){
  game_t* game = malloc(sizeof(struct _game));
  game->board = malloc(sizeof(struct _board));

  int row,  col,  cicle,  i = 0;

  FILE * flujo;
	flujo = fopen(filename, "r");
  fscanf(flujo, "%d %d %d",  &cicle , &row,  &col);
  game->cycles = cicle;
  board_init(game->board, row, col);

  char temp[col];
  while(i != col){
      fscanf(flujo,  "%s", temp);
      strcat(game->board->tablero, temp);
      i++;
  }
  fclose(flujo);
  board_init_def(game->board);
  return game;

}

void writeBoard(game_t *game, const char *filename){
  FILE* fichero;
  fichero = fopen(filename, "wt");
  fprintf(fichero, "%d %d %d",game->cycles,game->board->col,game->board->row);
  int i=0;
  int max = game->board->col*game->board->row;
  while (i<max){
    if(i%game->board->col==0)fprintf(fichero,"\n");
    fprintf(fichero,"%c",(game->board->tablero[i])?ALIVE:DEAD);
    i++;
  }
  fclose(fichero);

}


int cantvecinas(board_t *board, int i){//funcion a paralelizar
  int c = board->col;
  int f = board->row;
  char* t = board->tablero;
  int ret = 0;
  ret += t[f*((((i/f)-1)+f)%f)+((((i%c)-1)+c)%c)];
  ret += t[f*((((i/f)-1)+f)%f)+((((i%c)-0)+c)%c)];
  ret += t[f*((((i/f)-1)+f)%f)+((((i%c)+1)+c)%c)];

  ret += t[f*((((i/f)+0)+f)%f)+((((i%c)-1)+c)%c)];
  ret += t[f*((((i/f)+0)+f)%f)+((((i%c)+1)+c)%c)];

  ret += t[f*((((i/f)+1)+f)%f)+((((i%c)-1)+c)%c)];
  ret += t[f*((((i/f)+1)+f)%f)+((((i%c)+0)+c)%c)];
  ret += t[f*((((i/f)+1)+f)%f)+((((i%c)+1)+c)%c)];
  return ret;
}


void* update_particion(void *dato){
  for (int i = ((int*)dato)[0]; i < ((int*)dato)[1]; i++) {
    temp[i] = actual->tablero[i];
    int n = cantvecinas(actual,  i);
    if( n < 2 || n > 3)temp[i] = '\0';
    else if(n == 3)temp[i]='\1';
  }
}

void update(board_t *board, const int Nhilos){
  char temp1[board->row * board->col];
  actual = board;
  temp = temp1;

  int TamTablero = board->col * board->row;
  int particion = TamTablero / Nhilos;

  int arg[Nhilos][2];
  pthread_t hilos[Nhilos];

  size_t i = 0;
  for (; i < Nhilos-1; i++) {
    arg[i][0] = i * particion;
    arg[i][1] = i * particion + particion;
    pthread_create(&hilos[i],  NULL,  update_particion,  &arg[i]);
  }
  arg[i][0] = i * particion;
  arg[i][1] = TamTablero;
  pthread_create(&hilos[i],  NULL,  update_particion,  &arg[i]);


  for (size_t i = 0; i < Nhilos; i++) {
    pthread_join(hilos[i],  NULL);
  }
  board_load(board, temp);
}

board_t *congwayGoL(board_t *board,  unsigned int cycles,  const int nuproc){
  while (cycles) {
    update(board, nuproc);
    cycles--;
  }
  return board;
}

void game_destroy(game_t *game){
  board_destroy(game->board);
  free(game);
}
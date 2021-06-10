#include <stdio.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <unistd.h>
#include "game.h"

void rs(char* str,int cant) {
  for (int i = 0; i < cant; i++)printf("%s",str);
}
void irf(char *s1,char *s2,int cant,char *s3){
  printf("%s",s1 );
  rs(s2,cant);
  printf("%s",s3 );
}

void mostrarTablero(board_t *board,  unsigned int cycles,  const int nuproc) {
  char temp[100];
  sprintf(temp, "🕸 %d  🖇%d ║\n",nuproc,cycles);
  int n = board->col*2;
  irf("╔═","═",n,"╗\n");
  irf("║🎮 🇱 🇮 🇫 🇪​​​​​​​​​​'🇸  🇬 🇦 🇲 🇪   "," ",n-13-strlen(temp),temp);
  irf("╠╾","─",n-2,"─╼╣\n║");

  for(int i = 0; i < board->row*board->col; i++){
    if(i%board->row==0 && i>0)printf(" ║\n║");
    if(board->tablero[i])printf(" ■");
    else{printf(" ▢");}
  }
  irf(" ║\n╚","═",n,"═╝\n");
}

board_t *congwayGoLgrafico(board_t *board,  unsigned int cycles,  const int nuproc){
  int c=cycles;
  while (cycles) {
    update(board, nuproc);
    system("clear");
    mostrarTablero(board,c-cycles+1,nuproc);
    sleep(1);
    cycles--;
  }
  return board;
}


int main(int argc, char const *argv[]) {

  game_t* game = loadGame(argv[1]);

  if( argv[2] != NULL )game->board = congwayGoLgrafico(game->board, game->cycles, get_nprocs());
  else{
    game->board = congwayGoL(game->board, game->cycles, get_nprocs());
  }


  writeBoard(game, "salida.txt");
  game_destroy(game);
  return 0;
}

##Para compilar con interfaz gráfica
#programa: board.c game.c main.c
#	gcc board.c game.c main.c -lpthread && ./a.out test.txt 1
programa: board.c game.c main.c
	gcc board.c game.c main.c -lpthread && ./a.out test.txt

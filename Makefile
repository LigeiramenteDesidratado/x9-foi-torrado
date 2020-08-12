
all: game

game: main.o game.o screen.o
	gcc -Wall screen.o game.o main.o -o game -lSDL2

main.o: src/main.c
	gcc -c src/main.c

game.o: src/game.c src/game.h
	gcc -c src/game.c

screen.o: src/screen/screen.c src/screen/screen.h
	gcc -c src/screen/screen.c

clean:
	rm -f *.o game

all: game

game: main.o player.o
	g++ -o game.exe main.o player.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

clean:
	rm -f *.o

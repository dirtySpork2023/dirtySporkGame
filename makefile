all: game

game: main.o lib.o player.o bulletManager.o
	g++ -o game main.o lib.o player.o bulletManager.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

lib.o: lib.cpp lib.hpp
	g++ -c lib.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

bulletManager.o: bulletManager.cpp bulletManager.hpp
	g++ -c bulletManager.cpp

clean:
	rm -f *.o

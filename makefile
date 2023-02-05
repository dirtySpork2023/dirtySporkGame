all: game

game: main.o lib.o player.o bullet.o
	g++ -o game.exe main.o lib.o player.o bullet.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

lib.o: lib.cpp lib.hpp
	g++ -c lib.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

bullet.o: bullet.cpp bullet.hpp
	g++ -c bullet.cpp

clean:
	rm -f *.o

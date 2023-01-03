all: game

game: main.o player.o bullet.o
	g++ -o game.exe main.o player.o bullet.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

#func.o: func.cpp func.hpp
#	g++ -c func.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

bullet.o: bullet.cpp bullet.hpp
	g++ -c bullet.cpp

clean:
	rm -f *.o

game: main.o main.cpp player.o player.cpp player.hpp
	g++ -o game.exe main.o player.o -lncurses

main.o:
	g++ -c main.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

clean:
	rm -f *.o

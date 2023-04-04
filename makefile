all: game

game: main.o lib.o entity.o player.o kuba.o shooter.o bulletManager.o
	g++ -o game main.o lib.o entity.o player.o kuba.o shooter.o bulletManager.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

lib.o: lib.cpp lib.hpp
	g++ -c lib.cpp

entity.o: entity.cpp entity.hpp
	g++ -c entity.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

kuba.o: kuba.cpp kuba.hpp
	g++ -c kuba.cpp

shooter.o: shooter.cpp shooter.hpp
	g++ -c shooter.cpp

bulletManager.o: bulletManager.cpp bulletManager.hpp
	g++ -c bulletManager.cpp

clean:
	rm -f *.o game

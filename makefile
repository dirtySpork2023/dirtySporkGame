all: game

game: main.o lib.o entity.o player.o kuba.o shooter.o bulletManager.o level.o platform.o
	g++ -o game main.o lib.o entity.o player.o kuba.o shooter.o bulletManager.o level.o platform.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

lib.o: lib.cpp lib.hpp
	g++ -c lib.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

entity.o: entity.cpp entity.hpp
	g++ -c entity.cpp

kuba.o: kuba.cpp kuba.hpp
	g++ -c kuba.cpp

shooter.o: shooter.cpp shooter.hpp
	g++ -c shooter.cpp

yuck.o: yuck.cpp yuck.hpp
	g++ -c yuck.cpp

bulletManager.o: bulletManager.cpp bulletManager.hpp
	g++ -c bulletManager.cpp

level.o: level.cpp level.hpp
	g++ -c level.cpp

platform.o: platform.cpp platform.hpp
	g++ -c platform.cpp

clean:
	rm -f *.o game

all: game

game: main.o lib.o bulletManager.o entity.o shooter.o player.o powerup.o kuba.o yuck.o platform.o level.o
	g++ -o game main.o lib.o bulletManager.o entity.o shooter.o player.o powerup.o kuba.o yuck.o platform.o level.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

lib.o: lib.cpp lib.hpp
	g++ -c lib.cpp

bulletManager.o: bulletManager.cpp bulletManager.hpp
	g++ -c bulletManager.cpp

entity.o: entity.cpp entity.hpp
	g++ -c entity.cpp

shooter.o: shooter.cpp shooter.hpp
	g++ -c shooter.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

powerup.o: powerup.cpp powerup.hpp
	g++ -c powerup.cpp

kuba.o: kuba.cpp kuba.hpp
	g++ -c kuba.cpp

yuck.o: yuck.cpp yuck.hpp
	g++ -c yuck.cpp

platform.o: platform.cpp platform.hpp
	g++ -c platform.cpp

level.o: level.cpp level.hpp
	g++ -c level.cpp

clean:
	rm -f *.o game
all: game

game: main.o lib.o entity.o player.o kuba.o bulletManager.o powerup.o healthpowerup.o shieldpowerup.o
	g++ -o game main.o lib.o entity.o player.o kuba.o bulletManager.o powerup.o healthpowerup.o shieldpowerup.o -lncurses

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

bulletManager.o: bulletManager.cpp bulletManager.hpp
	g++ -c bulletManager.cpp

powerup.o: powerup.cpp powerup.hpp
	g++ -c powerup.cpp

healthpowerup.o: healthpowerup.cpp healthpowerup.hpp
	g++ -c healthpowerup.cpp

shieldpowerup.o: shieldpowerup.cpp shieldpowerup.hpp
	g++ -c shieldpowerup.cpp

clean:
	rm -f *.o game

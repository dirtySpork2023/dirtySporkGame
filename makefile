all: game

game: main.o lib.o bulletManager.o coin.o entity.o shooter.o player.o kuba.o yuck.o platform.o level.o menu.o
	g++ -o game main.o lib.o bulletManager.o coin.o entity.o shooter.o player.o kuba.o yuck.o platform.o level.o menu.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

lib.o: lib.cpp lib.hpp
	g++ -c lib.cpp

bulletManager.o: bulletManager.cpp bulletManager.hpp
	g++ -c bulletManager.cpp

coin.o: coin.cpp coin.hpp
	g++ -c coin.cpp

entity.o: entity.cpp entity.hpp
	g++ -c entity.cpp

shooter.o: shooter.cpp shooter.hpp
	g++ -c shooter.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

kuba.o: kuba.cpp kuba.hpp
	g++ -c kuba.cpp

yuck.o: yuck.cpp yuck.hpp
	g++ -c yuck.cpp

platform.o: platform.cpp platform.hpp
	g++ -c platform.cpp

level.o: level.cpp level.hpp
	g++ -c level.cpp

menu.o: menu.cpp menu.hpp
	g++ -c menu.cpp

reset:
	rm -f *.o game
	make all

clean:
	rm -f *.o
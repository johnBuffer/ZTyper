all: 

main.o: main.cpp
	g++ -Wall -O2 -std=c++11 -c ./main.cpp -o ./obj/main.o

PhyManager.o: PhyManager.cpp
	g++ -Wall -O2 -std=c++11 -c ./PhyManager.cpp -o ./obj/PhyManager.o

phyUtils.o: phyUtils.cpp
	g++ -Wall -O2 -std=c++11 -c ./phyUtils.cpp -o ./obj/phyUtils.o

Bullet.o: Bullet.cpp
	g++ -Wall -O2 -std=c++11 -c ./Bullet.cpp -o ./obj/Bullet.o

Entity2D.o: Entity2D.cpp
	g++ -Wall -O2 -std=c++11 -c ./Entity2D.cpp -o ./obj/Entity2D.o

Explosion.o: Explosion.cpp
	g++ -Wall -O2 -std=c++11 -c ./Explosion.cpp -o ./obj/Explosion.o

GameEngine.o: GameEngine.cpp
	g++ -Wall -O2 -std=c++11 -c ./GameEngine.cpp -o ./obj/GameEngine.o

Player.o: Player.cpp
	g++ -Wall -O2 -std=c++11 -c ./Player.cpp -o ./obj/Player.o

Zombie.o: Zombie.cpp
	g++ -Wall -O2 -std=c++11 -c ./Zombie.cpp -o ./obj/Zombie.o

all: main.o PhyManager.o phyUtils.o Bullet.o Entity2D.o Explosion.o GameEngine.o Player.o Zombie.o
	g++ ./obj/main.o ./obj/PhyManager.o ./obj/phyUtils.o ./obj/Bullet.o ./obj/Entity2D.o ./obj/Explosion.o ./obj/GameEngine.o ./obj/Player.o ./obj/Zombie.o -o ./bin/ZTyper -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm ./obj/*.o

all: main.o PhyManager.o phyUtils.o Bullet.o Entity2D.o Explosion.o GameEngine.o Player.o Zombie.o GameWorld.o SoundManager.o GUI.o ResourceManager.o json.o Sprite.o
	g++ ./obj/main.o ./obj/PhyManager.o ./obj/phyUtils.o ./obj/Bullet.o ./obj/Entity2D.o ./obj/Explosion.o ./obj/GameEngine.o ./obj/Player.o ./obj/Zombie.o ./obj/GameWorld.o ./obj/SoundManager.o ./obj/GUI.o ./obj/ResourceManager.o ./obj/json.o ./obj/Sprite.o -o ./bin/ZTyper -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

main.o: ./src/main.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/main.cpp -o ./obj/main.o

PhyManager.o: ./src/GameEngine/PhyManager.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/PhyManager.cpp -o ./obj/PhyManager.o

phyUtils.o: ./src/GameEngine/phyUtils.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/phyUtils.cpp -o ./obj/phyUtils.o

Bullet.o: ./src/GameEngine/Bullet.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/Bullet.cpp -o ./obj/Bullet.o

Entity2D.o: ./src/GameEngine/Entity2D.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/Entity2D.cpp -o ./obj/Entity2D.o

Explosion.o: ./src/GameEngine/Explosion.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/Explosion.cpp -o ./obj/Explosion.o

GameEngine.o: ./src/GameEngine/GameEngine.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/GameEngine.cpp -o ./obj/GameEngine.o

Player.o: ./src/GameEngine/Player.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/Player.cpp -o ./obj/Player.o

Zombie.o: ./src/GameEngine/Zombie.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/Zombie.cpp -o ./obj/Zombie.o

GameWorld.o: ./src/GameEngine/GameWorld.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/GameWorld.cpp -o ./obj/GameWorld.o

SoundManager.o: ./src/GameEngine/SoundManager.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/SoundManager.cpp -o ./obj/SoundManager.o

GUI.o: ./src/GameEngine/GUI.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/GameEngine/GUI.cpp -o ./obj/GUI.o

res: mainres.o ResourceManager.o Sprite.o json.o
	g++ ./obj/mainres.o ./obj/ResourceManager.o ./obj/Sprite.o ./obj/json.o -o ./bin/mainres -lsfml-graphics -lsfml-window -lsfml-system

mainres.o: ./src/ResourceManager/mainres.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/ResourceManager/mainres.cpp -o ./obj/mainres.o

ResourceManager.o: ./src/ResourceManager/ResourceManager.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/ResourceManager/ResourceManager.cpp -o ./obj/ResourceManager.o

json.o: ./src/json/jsoncpp.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/json/jsoncpp.cpp -o ./obj/json.o

Sprite.o: ./src/ResourceManager/Sprite.cpp
	g++ -Wall -O2 -std=c++11 -c ./src/ResourceManager/Sprite.cpp -o ./obj/Sprite.o

clean:
	rm ./obj/*.o
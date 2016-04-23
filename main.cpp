#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "PhyManager.h"
#include "GameEngine.h"

int main()
{
    int windowWidth = 750;
    int windowHeight = 700;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ZTyper", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    GameEngine gameEngine;

    Player* player = gameEngine.addPlayer(375, 600);

    for (int i(0); i<1; i++)
    {
        gameEngine.addZombie(rand()%10, rand()%50, rand()%10+10, player);
    }

    gameEngine.findTarget();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Escape) window.close();
                    break;
				}
				default:
                    break;
			}
        }

        gameEngine.update();

        window.clear();

        gameEngine.draw(&window);

        window.display();

    }

    return 0;
}

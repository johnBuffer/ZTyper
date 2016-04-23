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

    for (int i(0); i<100; i++)
    {
        gameEngine.addZombie(0, rand()%windowWidth, -rand()%5000, rand()%10+10, player);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    else if (event.key.code == sf::Keyboard::Tab)
                        player->setTarget(NULL);
                    break;
				}
				case sf::Event::TextEntered:
                {
                    if (player->getTarget())
                    {
                        player->shoot(event.text.unicode);
                    }
                    else
                    {
                        std::cout << "New target" << std::endl;
                        gameEngine.findTarget(event.text.unicode);
                    }
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

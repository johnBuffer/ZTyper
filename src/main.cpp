#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../includes/GameEngine/PhyManager.h"
#include "../includes/GameEngine/GameEngine.h"

int main()
{
    srand(time(NULL));

    int windowWidth = 1600;
    int windowHeight = 900;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ZTyper", sf::Style::Fullscreen, settings);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    GameEngine gameEngine(windowWidth, windowHeight);

    Player* player = gameEngine.addPlayer(windowWidth/2, windowHeight-200);

    while (window.isOpen())
    {
        //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //player->setPosition(mousePos.x, mousePos.y);

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
                    gameEngine.shoot(event.text.unicode);
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

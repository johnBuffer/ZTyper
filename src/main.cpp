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

    int windowWidth = 500;
    int windowHeight = 500;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ZTyper", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    GameEngine gameEngine(windowWidth, windowHeight);

    Player* player = gameEngine.addPlayer(windowWidth/2, windowHeight-200);

    sf::Texture heart;
    heart.loadFromFile("resources/textures/heart.png");

    sf::VertexArray sprite(sf::Quads, 4);
    sprite[0].texCoords = sf::Vector2f(0, 0);
    sprite[1].texCoords = sf::Vector2f(50, 0);
    sprite[2].texCoords = sf::Vector2f(50, 44);
    sprite[3].texCoords = sf::Vector2f(0, 44);

    double angle = 0;

    while (gameEngine.getGameStatus() && window.isOpen())
    {
        //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //player->setPosition(mousePos.x, mousePos.y);

        angle += 0.1;

        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    gameEngine.pause();
                }
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

#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "U_2DCollisionManager.h"
#include "U_2DOperators.h"

int main()
{
    int w_window = 750;
    int h_window = 500;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(w_window, h_window), "UnitedEngine", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Escape) window.close();

				}break;

        window.clear();

        window.display();

    }

    return 0;
}

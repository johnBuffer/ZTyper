#include "../../includes/GameEngine/GUI.h"
#include "../../includes/GameEngine/phyUtils.h"
#include "../../includes/ResourceManager/ResourceManager.h"

GUI::GUI():
    _player(NULL),
    _width(0),
    _height(0),
    _paused(false)
{
    _fontGUI.loadFromFile("resources/fonts/font.ttf");
    _text.setFont(_fontGUI);
}

GUI::GUI(Player* player, int width, int height):
    _player(player),
    _width(width),
    _height(height),
    _paused(false)
{
    _fontGUI.loadFromFile("resources/fonts/font.ttf");
    _text.setFont(_fontGUI);
    //_text.setCharacterSize(20);
    //_text.setColor(sf::Color::White);

    _heart.loadFromFile("resources/textures/heart.png");
}

void GUI::draw(sf::RenderTarget* renderer)
{
    sf::Texture* heartTex = ResourceManager<Sprite>::instance().get("heart")->tex();
    sf::Sprite heart(*heartTex); heart.setOrigin(25, 22);
    for (int life(0); life<_player->getLifes(); ++life)
    {
        heart.setPosition(_width-29, _height-29*(life+1));
        renderer->draw(heart);
    }

    _text.setPosition(10, _height-100);
    _text.setString(numberToString(_player->getScore()));
    _text.setColor(sf::Color::White);
    renderer->draw(_text);

    _text.setPosition(10, _height-40);
    _text.setString(numberToString(_player->getAccuracy())+" %");
    _text.setColor(sf::Color::White);
    renderer->draw(_text);

    if (_paused)
    {
        sf::RectangleShape hide(sf::Vector2f(_width, _height));
        hide.setFillColor(sf::Color(0, 0, 0, 200));
        _text.setString("PAUSE");
        _text.setPosition(_width/2-_text.getGlobalBounds().width/2, 200);

        renderer->draw(hide);
        renderer->draw(_text);
    }
}

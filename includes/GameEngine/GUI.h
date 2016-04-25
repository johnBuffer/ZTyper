#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "Player.h"
#include <SFML/Graphics.hpp>

class GUI
{
public:
    GUI();
    GUI(Player* player, int width, int height);

    void draw(sf::RenderTarget* renderer);
    void pause() {_paused = !_paused;}

private:
    Player*     _player;
    int         _width, _height;
    bool        _paused;
    sf::Texture _heart;
    sf::Font    _fontGUI;
    sf::Text    _text;
};

#endif // GUI_H_INCLUDED

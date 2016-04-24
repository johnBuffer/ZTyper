#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "../../json/json.h"

class Sprite
{
public:
	Sprite(const std::string& name, const std::string& path);
	Sprite(const std::string& name, const std::string& path, 
		int x, int y, int width, int height);
	virtual ~Sprite();

	std::string name();
	int x();
	int y();
	int width();
	int height();

	bool loadTexture();
	static bool loadAll(std::vector<Sprite*>* sprites);

private:
	std::string _name;
	std::string _path;
	sf::Texture* _tex;
	int _x;
	int _y;
	int _width;
	int _height;
};

#endif
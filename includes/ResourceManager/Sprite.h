#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
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
	sf::Vector2f topRight();
	sf::Vector2f topLeft();
	sf::Vector2f botLeft();
	sf::Vector2f botRight();
	sf::Texture* tex() const;

	static bool loadAll(std::vector< std::shared_ptr<Sprite> >* sprites);

private:
	std::string _name;
	std::string _path;
	sf::Texture* _tex;
	int _x;
	int _y;
	int _width;
	int _height;

	bool loadTexture();
};

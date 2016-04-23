#include "Sprite.h"

#include <iostream>

Sprite::Sprite(const std::string& name, const std::string& path) : Resource(name, path)
{
	std::cout << "Create Sprite." << std::endl;
}

Sprite::~Sprite()
{
	std::cout << "Delete Sprite." << std::endl;
}

bool Sprite::load()
{
	std::cout << "Sprite.load()." << std::endl;
	return false;
}

bool Sprite::loadAll()
{
	std::cout << "Sprite::loadAll()." << std::endl;
	return true;
}
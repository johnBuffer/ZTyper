#include "../../includes/ResourceManager/Sprite.h"

Sprite::Sprite(const std::string& name, const std::string& path) :
	_name(name), _path(path), _tex(nullptr), _x(0), _y(0), _width(0), _height(0)
{
	std::cout << "Create Sprite(0, 0, 0, 0)." << std::endl;
}


Sprite::Sprite(const std::string& name, const std::string& path,
	int x, int y, int width, int height) :
	_name(name), _path(path), _tex(nullptr), _x(x), _y(y), _width(width), _height(height)
{
	std::cout << "Create Sprite("
		<< std::to_string(x) << ", " << std::to_string(y) << ", "
		<< std::to_string(width) << ", " << std::to_string(height) << ")"
		<< std::endl;
}


Sprite::~Sprite()
{
	std::cout << "Delete Sprite("
		<< std::to_string(_x) << ", " << std::to_string(_y) << ", "
		<< std::to_string(_width) << ", " << std::to_string(_height) << ")"
		<< std::endl;

	delete _tex;
}

std::string Sprite::name() { return _name; }

int Sprite::x() { return _x; }

int Sprite::y() { return _y; }

int Sprite::width(){ return _width; }

int Sprite::height() { return _height; }


sf::Vector2f Sprite::topLeft() { return sf::Vector2f(_x, _y); }
sf::Vector2f Sprite::topRight() { return sf::Vector2f(_x + _width, _y); }
sf::Vector2f Sprite::botLeft() { return sf::Vector2f(_x, _y + _height); }
sf::Vector2f Sprite::botRight() {return sf::Vector2f(_x + _width, _y + _height); }

bool Sprite::loadTexture()
{
	std::cout << "Sprite.loadTexture() : " <<  "./resources/" + _path << std::endl;

	_tex = new sf::Texture();

	return (
		_tex->loadFromFile("./resources/" + _path, sf::IntRect(_x, _y, _width, _height))
	);
}

bool Sprite::loadAll(std::vector< std::shared_ptr<Sprite> >* sprites)
{

	std::cout << "Sprite::loadAll()." << std::endl;

	Json::Value root;
	Json::Reader reader;

	std::ifstream infile("./resources/ztyper.json");

	reader.parse(infile, root, false);

	Json::Value jSprites = root.get("sprites", "not found");

	for(Json::Value jSprite: jSprites)
	{
		std::string name = jSprite.get("name", "not found").asString();
		std::string path = jSprite.get("path", "not found").asString();
		int x = jSprite.get("x", 0).asInt();
		int y = jSprite.get("y", 0).asInt();
		int width = jSprite.get("width", 0).asInt();
		int height = jSprite.get("height", 0).asInt();

		std::shared_ptr<Sprite> sprite( new Sprite(name, path, x, y ,width, height) );

		sprite->loadTexture();

		sprites->push_back(sprite);
	}

	return sprites;
}

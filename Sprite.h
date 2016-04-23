#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "Resource.h"

class Sprite: public Resource
{
public:
	Sprite(const std::string& name, const std::string& path);
	virtual ~Sprite();
	virtual bool load();
	static bool loadAll();
};

#endif
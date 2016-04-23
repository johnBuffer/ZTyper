#include "../../includes/ResourceManager/Resource.h"

#include <iostream>

Resource::Resource(const std::string& name, const std::string& path)
{
	_name = name;
	_path = path;

	std::cout << "Create Resource." << std::endl;
}

Resource::~Resource()
{
	std::cout << "Delete Resource." << std::endl;
}

bool Resource::loadAll(){
	std::cout << "Resource::loadAll()." << std::endl;
	return true;
};

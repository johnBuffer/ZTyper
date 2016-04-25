#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Sprite.h"


template < class T >
class ResourceManager
{
public:
	static ResourceManager<T>& instance();

	std::shared_ptr<T> get(const std::string& name);
	bool loadAll();

private:
	ResourceManager() {};
	ResourceManager(ResourceManager<T> const&);
    void operator=(ResourceManager<T> const&);

	std::unordered_map< std::string, std::shared_ptr<T> > _map;

	bool add(std::shared_ptr<T> resource);
};

typedef ResourceManager<Sprite> SpriteManager;

template < class T >
ResourceManager<T>& ResourceManager<T>::instance()
{
	std::cout << "Get instance of ResourceManager." << std::endl;
    static ResourceManager<T> instance; // Guaranteed to be destroyed & Instantiated on first use.
    return instance;
}

template < class T >
bool ResourceManager<T>::loadAll()
{
	std::vector< std::shared_ptr<T> > resources;
	
	T::loadAll(&resources);

	for(auto resource: resources)
		add(resource);

	return true;
}

template < class T >
std::shared_ptr<T> ResourceManager<T>::get(const std::string& name)
{
	auto search = _map.find(name);

	return (search != _map.end()) ? search->second : nullptr;
}

template < class T >
bool ResourceManager<T>::add(std::shared_ptr<T> resource)
{
	return _map.insert({resource->name(), resource}).second;
}

#endif
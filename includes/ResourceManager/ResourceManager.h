#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Sprite.h"

// ResourceManager follow Singleton pattern.

template < class T >
class ResourceManager
{
public:
	// Getter/Constructor of the unique ResourceManager instance.
	static ResourceManager<T>& instance();

	// Load all Resources mentioned in ztyper.json.
	bool loadAll();

	// Retrieve a resource by its name.
	std::shared_ptr<T> get(const std::string& name);

private:
	// Constructors are private in order to avoid several instance 
	// of a ResourceManager.
	ResourceManager() {};
	ResourceManager(ResourceManager<T> const&);
    void operator=(ResourceManager<T> const&);

    // Structure to store the resources by their name.
	std::unordered_map< std::string, std::shared_ptr<T> > _map;

	// Insert a resource in the map structure.
	bool add(std::shared_ptr<T> resource);
};

typedef ResourceManager<Sprite> SpriteManager;

template < class T >
ResourceManager<T>& ResourceManager<T>::instance()
{
	//std::cout << "Get instance of ResourceManager." << std::endl;
    static ResourceManager<T> instance;
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

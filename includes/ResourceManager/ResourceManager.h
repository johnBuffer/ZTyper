#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>


template < class T >
class ResourceManager
{

public:
	ResourceManager();
	virtual ~ResourceManager();

	std::shared_ptr<T> get(const std::string& name);
	bool add(const std::string& name, const std::string& path);
	bool loadAll();

private:
	std::unordered_map< std::string, std::shared_ptr<T> > _map;

	bool add(std::shared_ptr<T> resource);
};


template < class T >
ResourceManager<T>::ResourceManager()
{
	std::cout << "Create ResourceManager." << std::endl;
}

template < class T >
ResourceManager<T>::~ResourceManager()
{
	std::cout << "Delete ResourceManager." << std::endl;
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
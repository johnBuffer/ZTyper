#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

template < class T >
class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	T* get(const std::string& name);
	bool add(const std::string& name, const std::string& path);
	bool loadAll();

private:
	std::unordered_map< std::string, T*> _map;

	bool add(T* resource);
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
	std::vector<T*> resources;
	
	T::loadAll(&resources);

	for(T* resource: resources)
		add(resource);

	return true;
}

template < class T >
T* ResourceManager<T>::get(const std::string& name)
{
	auto search = _map.find(name);

	return (search != _map.end()) ? search->second : nullptr;
}

template < class T >
bool ResourceManager<T>::add(T* resource)
{
	return _map.insert({resource->name(), resource}).second;
}

#endif
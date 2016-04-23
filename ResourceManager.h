#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <string>
#include <iostream>
#include <unordered_map>

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
	return T::loadAll();
}


#endif
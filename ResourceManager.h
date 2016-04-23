#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

template <class T>
class ResourceManager
{
public:
	T* get(const std::string& name);

private:
	std::unordered_map< std::string, T*> _map
}
#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <string>

class Resource
{
protected:
	std::string _name;
	std::string _path; 

	Resource(const std::string& name, const std::string& path);

	static bool loadAll();

	virtual ~Resource();
	virtual bool load() = 0;
};

#endif
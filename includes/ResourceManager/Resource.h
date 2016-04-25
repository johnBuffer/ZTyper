#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <string>

class Resource
{
protected:
	 

	Resource(const std::string& name, const std::string& path);
	virtual ~Resource();
	
	//virtual bool load() = 0;
};

#endif
#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

class Resource
{
public:
	std::string _name;
	std::string _path;

	virtual bool load();
};

#endif
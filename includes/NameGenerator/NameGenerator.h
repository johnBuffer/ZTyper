#pragma once

#include "../json/json.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class NameGenerator
{
private:
	static std::vector<std::string> _surnames;
	static std::vector<std::string> _adjectives;
	static int _randomSeed;
	
	static bool loadAll();
	
public:
	NameGenerator();
	std::string getRandomName();
};
#pragma once

class NameGenerator
{
private:
	static std::vector<std::string> surnames;
	static std::vector<std::string> adjectives;
	
	static bool loadAll();
	
public:
	std::string getRandomName();

}
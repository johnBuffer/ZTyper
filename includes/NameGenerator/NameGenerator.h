#pragma once

class NameGenerator
{
private:
	std::vector<std::string> surnames;
	std::vector<std::string> adjectives;
	
public:
	std::string getRandomName();
}
#include "../../includes/NameGenerator/NameGenerator.h"

std::vector<std::string> NameGenerator::_surnames;
std::vector<std::string> NameGenerator::_adjectives;

NameGenerator::NameGenerator()
{
	std::srand(std::time(0));
}


std::string NameGenerator::getRandomName()
{
	if (_surnames.size() == 0 || _adjectives.size() == 0)
		NameGenerator::loadAll();

    int i = std::rand() % _surnames.size();

    int j = std::rand() % _adjectives.size();

    return _surnames[i] + " the " + _adjectives[j];
}


bool NameGenerator::loadAll()
{
	std::cout << "NameGenerator::loadAll()." << std::endl;

	Json::Value root;
	Json::Reader reader;

	std::ifstream infile("./resources/texts/names.json");

	reader.parse(infile, root, false);

	Json::Value surnames = root.get("surnames", false);

	if (!surnames)
		return false;

	for(Json::Value surname: surnames)
		_surnames.push_back(surname.asString());


	Json::Value adjectives = root.get("adjectives", false);

	if (!adjectives)
		return false;

	for(Json::Value adjective: adjectives)
		_adjectives.push_back(adjective.asString());

	return true;
}
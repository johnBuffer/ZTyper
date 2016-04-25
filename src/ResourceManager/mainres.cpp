#include <stdlib.h>
#include "../../includes/ResourceManager/ResourceManager.h"
#include "../../includes/ResourceManager/Sprite.h"


int main()
{

	ResourceManager<Sprite> rm;

	rm.loadAll();

	auto sp1 = rm.get("zombie_1");
	std::cout << sp1->name() << std::endl;

	auto sp2 = rm.get("zombie_2");
	std::cout << sp2->name() << std::endl;

	auto sp3 = rm.get("zombie_3");
	std::cout << sp3->name() << std::endl;
}


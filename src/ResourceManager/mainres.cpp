#include <stdlib.h>
#include "../../includes/ResourceManager/ResourceManager.h"
#include "../../includes/ResourceManager/Sprite.h"


int main()
{


	SpriteManager& sm = SpriteManager::instance();

	sm.loadAll();
	sm.get("zombie_1");

	auto sp1 = sm.get("zombie_1");
	std::cout << sp1->name() << std::endl;

	auto sp2 = sm.get("zombie_2");
	std::cout << sp2->name() << std::endl;

	auto sp3 = sm.get("zombie_3");
	std::cout << sp3->name() << std::endl;

}


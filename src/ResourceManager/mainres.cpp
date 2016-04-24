#include <stdlib.h>
#include "../../includes/ResourceManager/ResourceManager.h"
#include "../../includes/ResourceManager/Sprite.h"


int main()
{

	ResourceManager<Sprite> rm;
	
	rm.loadAll();


	Sprite* sp = rm.get("zombie");

	std::cout << sp->name() << std::endl;
}


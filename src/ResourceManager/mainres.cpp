#include <stdlib.h>
#include "../../json/json.h"
#include "../../includes/ResourceManager/ResourceManager.h"
#include "../../includes/ResourceManager/Sprite.h"


int main()
{
	ResourceManager<Sprite> rm;

	Sprite sp("le_nom", "le_path");

	rm.loadAll();
	return 0;
}

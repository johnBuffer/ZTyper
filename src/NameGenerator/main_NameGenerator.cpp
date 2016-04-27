#include <stdlib.h>
#include <iostream>
#include "../../includes/NameGenerator/NameGenerator.h"

int main()
{
	NameGenerator ng;

	for(int i=0; i < 20 ; i++)
		std::cout << ng.getRandomName() << std::endl;

}
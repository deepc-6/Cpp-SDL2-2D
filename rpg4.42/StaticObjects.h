#include "Header.h"
#include "AllObjects.h"

class StaticObjects
{
public:
	StaticObjects();
	static bool InputWallFromFile(std::vector<AllObjects*> *wall);
};
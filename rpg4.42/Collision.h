#pragma once

#include "AllObjects.h"

class Collision
{
private:
	static void InputFromFile();
public:
	Collision();
	static void onInit();
	static bool updateObjectAfterCheckingCollision(AllObjects *object);
	static bool willCollide(AllObjects *object);
};
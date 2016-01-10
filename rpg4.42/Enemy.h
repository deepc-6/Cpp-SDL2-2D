#pragma once

#include "AllObjects.h"

class Enemy: public AllObjects
{
public:
	Enemy();
	Enemy(std::string filePath, int x, int y, int framesX, int framesY, char passedID);
	void Draw();
	void Move(float delta);
	bool left;
};
#pragma once

#include "AllObjects.h"

class Player: public AllObjects
{
private:
	const Uint8 *keyState;
	bool left;
public:
	Player();
	Player(std::string filePath, int x, int y, int framesX, int framesY, char passedID);
	void Draw();
	void Move(float delta);
};
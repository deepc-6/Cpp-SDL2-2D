#include "Main.h"

void Main::onMove()
{
	//Animating Player and Enemy
	player1->Move(delta);
	for (int i = 0; i < numOfEnemies; i++)
		allEnemies[i]->Move(delta);

	//Defining Camera Rectangle
	cameraRect.x = player1->positionRect.x - 960;
	cameraRect.y = player1->positionRect.y - 540;

	//Setting Boundary of Camera Rectangle
	if (cameraRect.x < 0)
		cameraRect.x = 0;
	if (cameraRect.y < 0)
		cameraRect.y = 0;

	//Fix Stretching Effect when cameraRect reaches halfway of screenSize
	if (cameraRect.x > levelWidth / 2)
		cameraRect.x = levelWidth / 2;
	if (cameraRect.y > levelHeight / 2)
		cameraRect.y = levelHeight / 2;
}
#include "Main.h"

SDL_Renderer *Main::renderTarget;
SDL_Rect Main::cameraRect;

Main::Main()
{
	isRunning = true;
	numOfEnemies = 7;
	numOfTreasures = 4;
	enemyX = 3 * GRANULARITY;
	enemyY = 32 * GRANULARITY;
	treasureX = 13 * GRANULARITY;
	treasureY = 11 * GRANULARITY;
	wall1X = 0;
	wall2X = 0;
	currentTime = 0;
	prevTime = 0;
	delta = 0.0f;
	cameraRect = { 0, 0, levelWidth / 2, levelHeight / 2 };
}

int main(int argc, char** argv)
{
	Main game;
	return game.onExecute();
}
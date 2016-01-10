#pragma once

#include "Collision.h"
#include "Player.h"
#include "Enemy.h"

class Main
{
private:
	SDL_Window *window;
	SDL_Texture *background;
	SDL_Event event;
	Player *player1;
	AllObjects *goal;
	std::vector<AllObjects*> allStaticAllObjects;
	std::vector<Enemy*> allEnemies;
	std::vector<AllObjects*> allTreasures;
	int bgWidth, bgHeight;
	int numOfEnemies, numOfTreasures;
	int enemyX, enemyY;
	int treasureX, treasureY;
	int wall1X, wall2X;
	int currentTime, prevTime;
	float delta;	
	bool onInit();
	int onLoad();
	void InputFromFile();
	void onEvent();
	void onMove();
	void onRender();
	void onCleanup();
public:
	Main();
	static SDL_Renderer *renderTarget;
	static SDL_Rect cameraRect;
	int onExecute();
	bool isRunning;
};
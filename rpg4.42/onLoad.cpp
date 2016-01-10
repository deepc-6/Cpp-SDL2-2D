#include "Main.h"
#include "Player.h"
#include "StaticObjects.h"

int Main::onLoad()
{
	background = IMG_LoadTexture(renderTarget, "data/grass.bmp");
	SDL_QueryTexture(background, NULL, NULL, &bgWidth, &bgHeight);

	Collision::onInit();	
	if (StaticObjects::InputWallFromFile(&allStaticAllObjects) == false)
		return -1;

	Path::AnalysePathsFromCollision();

	player1 = new Player("data/player.png",  2 * GRANULARITY, 2 * GRANULARITY, 3, 4, PLAYER);
	
	for (int i = 0; i < numOfTreasures; i++)
	{
		AllObjects *treasure = new AllObjects("data/treasure.png", treasureX, treasureY, 1, 1, WALL);
		allTreasures.push_back(treasure);
		treasureX += 15 * GRANULARITY;
	}

	goal = new AllObjects("data/goal.png", 55 * GRANULARITY, 12 * GRANULARITY, 1, 1, WALL);

	for (int i = 0; i < numOfEnemies; i++)
	{
		Enemy *enemy = new Enemy("data/enemy.png", enemyX, enemyY, 1, 1, i);
		allEnemies.push_back(enemy);		
		enemy->path.findPath(enemyX / GRANULARITY, enemyY / GRANULARITY);
		enemyX += 10 * GRANULARITY;
	}
	return 0;
}
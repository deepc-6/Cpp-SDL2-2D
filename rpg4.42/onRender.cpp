#include "Main.h"

void Main::onRender()
{
	SDL_RenderClear(renderTarget);

	SDL_RenderCopy(renderTarget, background, &cameraRect, NULL);
	
	//Wall
	for (AllObjects *wall : allStaticAllObjects)
		wall->Draw();

	//Goal
	goal->Draw();

	//Player
	player1->Draw();
	
	//Treasures
	for (AllObjects *treasure: allTreasures)
		treasure->Draw();
	
	//Enemies
	for (Enemy *enemy: allEnemies)
		enemy->Draw();
		
	SDL_RenderPresent(renderTarget);
}
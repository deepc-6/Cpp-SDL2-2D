#include "Main.h"

void Main::onCleanup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(background);
	background = nullptr;
	window = nullptr;
	renderTarget = nullptr;
	IMG_Quit();
	SDL_Quit();
}
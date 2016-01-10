#include "Main.h"

void Main::onEvent()
{
	//Event Handling
	if (event.type == SDL_QUIT)
		isRunning = false;
	if (event.key.keysym.sym == SDLK_ESCAPE)
		isRunning = false;
}
#include "Main.h"

int Main::onExecute()
{
	if (onInit() == false)
		return -1;	

	onLoad();

	while (isRunning)
	{
		//Making sure movement and animation run at the same time on all systems
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;
		
		while (SDL_PollEvent(&event))
		{
			onEvent();
		}
		
		onMove();
		onRender();
	}
	onCleanup();
	return 0;
}
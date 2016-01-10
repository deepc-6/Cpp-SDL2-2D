#include "Collision.h"
#include "Main.h"

std::map<std::string, SDL_Texture*> AllObjects::textureList;

AllObjects::AllObjects()
{

}

AllObjects::AllObjects(std::string filePath, int x, int y, int framesX, int framesY, char passedID)
{
	std::map<std::string, SDL_Texture*>::iterator it = textureList.find(filePath);
	correction = 1;
	if (it != textureList.end())
		texture = textureList[filePath];
	else
	{
		texture = IMG_LoadTexture(Main::renderTarget, filePath.c_str());
		textureList[filePath] = texture;
	}
	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	id = passedID;

	positionRect.x = x;
	positionRect.y = y;

	//Cropping the sprite to animate
	textureWidth = cropRect.w;

	cropRect.x = 0;
	cropRect.y = 0;
	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	oldPositionRect = positionRect;
	nextPositionRect = positionRect;

	Collision::updateObjectAfterCheckingCollision(this);

	moveSpeed = 500.0f;

	//path.findPath(positionRect.x, positionRect.y);
}

void AllObjects::Move(float delta)
{
	//To make AllObjects stop after reaching destination
	int index = path.currentIndex;

	//To keep AllObjects moving again in the same loop after reaching destination
	//int index = path.currentIndex < path.destinations.size() ? path.currentIndex : 0;

	//If AllObjects moves after reaching destination, omit this part
	if (path.currentIndex >= (signed)path.roadMap.size())
		return;

	Destination *d = path.roadMap.at(index);
	int direction = d->direction;
	int stepSize = correction * (int(moveSpeed * delta) % GRANULARITY);

	if (d->numberOfSteps >= d->currentStep)
	{
		d->currentStep += abs(stepSize);

		if (direction == LEFT)
		{
			nextPositionRect.x = nextPositionRect.x - stepSize;
		}
		else if (direction == RIGHT)
		{
			nextPositionRect.x = nextPositionRect.x + stepSize;
		}
		else if (direction == UP)
		{
			nextPositionRect.y = nextPositionRect.y - stepSize;
		}
		else if (direction == DOWN)
		{
			nextPositionRect.y = nextPositionRect.y + stepSize;
		}
	}
	else
	{
		if (correction == 1)
			path.currentIndex++;
		correction = 1;

		d->currentStep = 0;
	}

	//Collision
	if (!Collision::updateObjectAfterCheckingCollision(this))
	{
		correction = -correction;
		d->currentStep = d->numberOfSteps - d->currentStep - stepSize;
	}
}

void AllObjects::Draw()
{
	drawingRect = { positionRect.x - Main::cameraRect.x, positionRect.y - Main::cameraRect.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(Main::renderTarget, texture, &cropRect, &drawingRect);
}
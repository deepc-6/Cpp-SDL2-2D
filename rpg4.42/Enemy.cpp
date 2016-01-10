#include "Enemy.h"
#include "Collision.h"
#include "Main.h"

Enemy::Enemy()
{

}

Enemy::Enemy(std::string filePath, int x, int y, int framesX, int framesY, char passedID) :
AllObjects(filePath, x, y, framesX, framesY, passedID)
{
	moveSpeed = 200.0f;
}

void Enemy::Move(float delta)
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
			left = true;
		}
		else if (direction == RIGHT)
		{
			nextPositionRect.x = nextPositionRect.x + stepSize;
			left = false;
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

void Enemy::Draw()
{
	float adjustmentX = 0;
	float adjustmentY = 0;

	adjustmentY = float(positionRect.h / 1.5f);
	
	drawingRect = { positionRect.x - int(adjustmentX) - Main::cameraRect.x, positionRect.y - int(adjustmentY) - Main::cameraRect.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(Main::renderTarget, texture, &cropRect, &drawingRect);
}
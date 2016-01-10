#include "Player.h"
#include "Collision.h"
#include "Main.h"

Player::Player()
{

}

Player::Player(std::string filePath, int x, int y, int framesX, int framesY, char passedID) : 
AllObjects(filePath, x, y, framesX, framesY, passedID)
{
	left = false;
	isActive = false;
	moveSpeed = 500.0f;
}

void Player::Move(float delta)
{
	keyState = SDL_GetKeyboardState(NULL);

	isActive = true;

	if (keyState[SDL_SCANCODE_W])
	{
		nextPositionRect.y -= (int(moveSpeed * delta) % GRANULARITY);
		cropRect.y = frameHeight * 3;
	}
	else if (keyState[SDL_SCANCODE_S])
	{
		nextPositionRect.y += (int(moveSpeed * delta) % GRANULARITY);
		cropRect.y = 0;
	}

	if (keyState[SDL_SCANCODE_A])
	{
		nextPositionRect.x -= (int(moveSpeed * delta) % GRANULARITY);
		cropRect.y = frameHeight;
		left = true;
	}
	else if (keyState[SDL_SCANCODE_D])
	{
		nextPositionRect.x += (int(moveSpeed * delta) % GRANULARITY);
		cropRect.y = frameHeight * 2;
		left = false;
	}
	else
		isActive = false;

	if (isActive)
	{
		frameCounter += delta;
		if (frameCounter >= 0.25f)
		{
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;
		}
	}
	else
	{
		frameCounter = 0;
		cropRect.x = frameWidth;
	}

	//Collision
	(Collision::updateObjectAfterCheckingCollision(this));
}

void Player::Draw()
{
	float adjustmentX = 0;
	float adjustmentY = 0;

	if (left)
	adjustmentX = float(positionRect.w / 5.0f);
	else if (!left)
	adjustmentX = float(positionRect.w);
	adjustmentY = float(positionRect.h);

	SDL_Rect drawingRect = { positionRect.x - int(adjustmentX) - Main::cameraRect.x, positionRect.y - Main::cameraRect.y - int(adjustmentY), positionRect.w, positionRect.h };
	SDL_RenderCopy(Main::renderTarget, texture, &cropRect, &drawingRect);
}
#pragma once

#include "Header.h"
#include "Path.h"

class AllObjects
{
private:
	static std::map<std::string, SDL_Texture*> textureList;
	float delta;
public:
	AllObjects();
	AllObjects(std::string filePath, int x, int y, int framesX, int framesY, char passedID);
	Path path;
	SDL_Texture *texture;
	SDL_Rect drawingRect;
	SDL_Rect cropRect;
	SDL_Rect positionRect;
	SDL_Rect nextPositionRect;
	SDL_Rect oldPositionRect;
	bool isActive;
	float moveSpeed;
	float frameCounter;
	int frameWidth, frameHeight, textureWidth;
	char id;
	int correction;
	virtual void Move(float delta);
	void Draw();
};
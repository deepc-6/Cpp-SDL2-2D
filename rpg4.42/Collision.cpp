#include "Collision.h"

char collisionMap[levelWidth / GRANULARITY][levelHeight / GRANULARITY];

Collision::Collision()
{
	
}

void Collision::onInit()
{
	for (int i = 0; i < levelWidth / GRANULARITY; i++)
	{
		for (int j = 0; j < levelHeight / GRANULARITY; j++)
		{
			collisionMap[i][j] = FREESPACE;
		}
	}

	for (int i = 0; i < levelWidth / GRANULARITY; i++)
	{
		collisionMap[i][0] = BOUNDARY;
		collisionMap[i][levelHeight / GRANULARITY] = BOUNDARY;
	}
	for (int i = 0; i < levelHeight / GRANULARITY; i++)
	{
		collisionMap[0][i] = BOUNDARY;
		collisionMap[levelWidth / GRANULARITY][i] = BOUNDARY;
	}
}

bool Collision::updateObjectAfterCheckingCollision(AllObjects *object)
{
	if (!willCollide(object))
	{
		object->oldPositionRect = object->positionRect;
		object->positionRect = object->nextPositionRect;

		for (unsigned int i = 0; i < TEXTURESIZE / GRANULARITY; i++)
		{
			collisionMap[(object->oldPositionRect.x) / GRANULARITY][(object->oldPositionRect.y) / GRANULARITY] = FREESPACE;
			collisionMap[(object->nextPositionRect.x) / GRANULARITY][(object->nextPositionRect.y) / GRANULARITY] = object->id;
		}
		return true;
	}
	else
	{
		object->nextPositionRect = object->positionRect;
		return false;
	}
}

bool Collision::willCollide(AllObjects *object)
{
	unsigned int x = object->nextPositionRect.x / GRANULARITY;
	unsigned int y = object->nextPositionRect.y / GRANULARITY;

	for (unsigned int i = x; i < x + TEXTURESIZE / GRANULARITY; i++)
	{
		for (unsigned int j = y; j < y + TEXTURESIZE / GRANULARITY; j++)
		{
			if ((collisionMap[i][j] != FREESPACE) && (collisionMap[i][j] != object->id))
				return true;
		}
	}
	return false;
}
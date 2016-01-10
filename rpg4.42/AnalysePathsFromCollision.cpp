#include "Path.h"
#include "Collision.h"

extern char collisionMap[levelWidth / GRANULARITY][levelHeight / GRANULARITY];

void Path::AnalysePathsFromCollision()
{
	Destination *startpoint = new Destination(1, 1, 0, 0);
	Path::destinations->push_back(startpoint);

	for (int i = 0; i < (signed)Path::destinations->size(); i++)
	{
		Destination *c = Path::destinations->at(i);
		int x = c->x;
		int y = c->y;
		collisionMap[c->x][c->y] = TEMP;

		AnalyseLeftMovement(x, y, c);
		AnalyseRightMovement(x, y, c);
		AnalyseUpMovement(x, y, c);
		AnalyseDownMovement(x, y, c);
	}

	/*
	std::cout << "Size is " << Path::destinations->size() << std::endl;

	for (int i = 0; i < (signed)Path::destinations->size(); i++)
	{
		Destination *dest = Path::destinations->at(i);

		dest->Print();
	}
	*/

	for (int i = 0; i <= levelHeight / GRANULARITY; i++)
	{
		for (int j = 0; j <= levelWidth / GRANULARITY; j++)
		{
			if (collisionMap[j][i] == TEMP)
				collisionMap[j][i] = FREESPACE;

			//writeFile("data/output.txt");
		}
	}
}


void Path::AnalyseLeftMovement(int x, int y, Destination *c)
{
	int endOfPath = 0;
	Destination * found = NULL;
	Destination * neighborsFound = NULL;

	for (x = c->x, y = c->y - 1; y > 0; y--)
	{
		if (collisionMap[x][y] != FREESPACE)
		{
			if (collisionMap[x][y] != TEMP)
			{
				endOfPath = 1;
				y++;
			}
			break;
		}
		if ((collisionMap[x + 1][y] == FREESPACE || collisionMap[x + 1][y] == TEMP) && x + 1 < levelWidth / GRANULARITY)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
		if ((collisionMap[x - 1][y] == FREESPACE || collisionMap[x - 1][y] == TEMP) && x - 1 >= 0)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
	}

	if (y <= 0)
		endOfPath = 1;

	y = y < 0 ? 1 : y + 1;

	if (collisionMap[x][y] == FREESPACE && (endOfPath == 1 || y == 0))
	{
		collisionMap[x][y] = TEMP;
		found = AddIfDestinationNotPresent(x, y);
		neighborsFound = AddIfNeighborsNotPresent(x, y, c);
		AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
	}
}

void Path::AnalyseRightMovement(int x, int y, Destination *c)
{
	int endOfPath = 0;
	Destination * found = NULL;
	Destination * neighborsFound = NULL;

	for (x = c->x, y = c->y + 1; y < levelHeight / GRANULARITY; y++)
	{
		if (collisionMap[x][y] != FREESPACE)
		{
			if (collisionMap[x][y] != TEMP)
			{
				endOfPath = 1;
				y--;
			}
			break;
		}
		if ((collisionMap[x + 1][y] == FREESPACE || collisionMap[x + 1][y] == TEMP) && x + 1 < levelWidth / GRANULARITY)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
		if ((collisionMap[x - 1][y] == FREESPACE || collisionMap[x - 1][y] == TEMP) && x - 1 >= 0)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
	}

	if (y >= levelHeight / GRANULARITY - 1)
		endOfPath = 1;

	y = y >= levelHeight / GRANULARITY - 1 ? levelHeight / GRANULARITY - 1 : y;

	if (collisionMap[x][y] == FREESPACE && (endOfPath == 1 || y == levelHeight / GRANULARITY))
	{
		collisionMap[x][y] = TEMP;
		found = AddIfDestinationNotPresent(x, y);
		neighborsFound = AddIfNeighborsNotPresent(x, y, c);
		AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
	}
}

void Path::AnalyseUpMovement(int x, int y, Destination *c)
{
	int endOfPath = 0;
	Destination * found = NULL;
	Destination * neighborsFound = NULL;

	for (x = c->x - 1, y = c->y; x <= levelWidth / GRANULARITY; x--)
	{
		if (collisionMap[x][y] != FREESPACE)
		{
			if (collisionMap[x][y] != TEMP)
			{
				endOfPath = 1;
				x++;
			}
			break;
		}
		if ((collisionMap[x][y + 1] == FREESPACE || collisionMap[x][y + 1] == TEMP) && y + 1 < levelHeight / GRANULARITY)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
		if ((collisionMap[x][y - 1] == FREESPACE || collisionMap[x][y - 1] == TEMP) && y - 1 >= 0)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
	}

	if (x <= 0)
		endOfPath = 1;

	x = x <= 0 ? 0 : x;

	if (collisionMap[x][y] == FREESPACE && (endOfPath == 1 || x == levelWidth / GRANULARITY - 1))
	{
		collisionMap[x][y] = TEMP;
		found = AddIfDestinationNotPresent(x, y);
		neighborsFound = AddIfNeighborsNotPresent(x, y, c);
		AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
	}
}

void Path::AnalyseDownMovement(int x, int y, Destination *c)
{
	int endOfPath = 0;
	Destination * found = NULL;
	Destination * neighborsFound = NULL;

	for (x = c->x + 1, y = c->y; x < levelWidth / GRANULARITY; x++)
	{
		if (collisionMap[x][y] != FREESPACE)
		{
			if (collisionMap[x][y] != TEMP)
			{
				endOfPath = 1;
				x--;
			}
			break;
		}
		if ((collisionMap[x][y + 1] == FREESPACE || collisionMap[x][y + 1] == TEMP) && y + 1 < levelHeight / GRANULARITY)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
		if ((collisionMap[x][y - 1] == FREESPACE || collisionMap[x][y - 1] == TEMP) && y - 1 >= 0)
		{
			collisionMap[x][y] = TEMP;
			found = AddIfDestinationNotPresent(x, y);
			neighborsFound = AddIfNeighborsNotPresent(x, y, c);
			AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
		}
	}

	if (x >= levelWidth / GRANULARITY)
		endOfPath = 1;

	x = x >= levelWidth / GRANULARITY ? levelWidth / GRANULARITY - 1 : x;

	if (collisionMap[x][y] == FREESPACE && (endOfPath == 1 || x == levelWidth / GRANULARITY - 1))
	{
		collisionMap[x][y] = TEMP;
		found = AddIfDestinationNotPresent(x, y);
		neighborsFound = AddIfNeighborsNotPresent(x, y, c);
		AddIfNeighborsNotPresent(c->x, c->y, neighborsFound);
	}
}
#include "Path.h"
#include "Collision.h"

extern char collisionMap[levelWidth / GRANULARITY][levelHeight / GRANULARITY];
std::vector<Destination *> *Path::destinations = NULL;

Path::Path()
{
	if (destinations == NULL)
		destinations = new std::vector<Destination *>();
	currentIndex = 0;
}

Direction Path::findDirection(int frmx, int frmy, int tox, int toy)
{
	Direction direction = RIGHT;
	if (frmx == tox && frmy > toy)
		direction = UP;
	else if (frmx == tox && frmy <= toy)
		direction = DOWN;
	else if (frmy == toy && frmx > tox)
		direction = LEFT;
	else
		direction = RIGHT;
	return direction;
}

int Path::findDistance(int frmx, int frmy, int tox, int toy)
{
	int distance;
	if (frmx == tox)
		distance = abs(frmy - toy);
	else
		distance = abs(frmx - tox);
	return distance;
}

void Path::findPath(int x, int y)
{
	Destination *dest = Path::findNeighbors(x, y);
	Destination * current = &Destination(x, y, 0, 0);
	if (dest == NULL) {
		for (int i = 0; i < signed(destinations->size()); i++)
			destinations->at(i)->Print();
		std::cout << "Could not find location" << std::endl;
		return;
	}
	Direction direction;
	int distance = 0;
	for (int i = 0; i < 120; i++)
	{
		direction = findDirection(current->x, current->y, dest->x, dest->y);
		distance = findDistance(current->x, current->y, dest->x, dest->y);
		//const char *arr[] = {"Left", "Right", "Up", "Down"};
		//std::cout << "Going " << arr[direction] << "distance " << distance << std::endl;
		roadMap.push_back(new Destination(dest->x, dest->y, direction, distance * GRANULARITY));
		current = dest;
		int random = rand() % current->neighbors.size();
		dest = current->neighbors.at(random);
	}
}

void Path::Guide(std::vector<Destination*> *destinations)
{
	destinations->push_back(new Destination(0, 0, LEFT, 1 * 64));
	destinations->push_back(new Destination(0, 0, RIGHT, 57 * 64));
}

void Path::writeFile(std::string fileName)
{
	std::ofstream outFile;
	outFile.open(fileName);

	for (int i = 0; i <= levelHeight / GRANULARITY; i++)
	{
		for (int j = 0; j <= levelWidth / GRANULARITY; j++)
		{
			outFile << collisionMap[j][i];
		}
		outFile << std::endl;
	}
	outFile.close();
}

Destination* Path::findNeighbors(int x, int y)
{
	for (int i = 0; i < (signed)Path::destinations->size(); i++)
	{
		Destination *dest = Path::destinations->at(i);

		for (Destination * neighbor : dest->neighbors)
		{
			if ((dest->x == x  && dest->x == neighbor->x) || (dest->y == y  && dest->y == neighbor->y))
			{
				return dest;
			}
		}
	}
	return NULL;
}

Destination* Path::AddIfDestinationNotPresent(int x, int y)
{
	int i;
	Destination *found = NULL;

	for (i = 0; i < (signed)Path::destinations->size(); i++)
	{
		if (x == Path::destinations->at(i)->x && y == Path::destinations->at(i)->y) {
			found = Path::destinations->at(i);
			break;
		}
	}
	if (found == NULL)
	{
		found = new Destination(x, y, 0, 0);

		Path::destinations->push_back(found);
	}
	return found;
}

Destination* Path::AddIfNeighborsNotPresent(int x, int y, Destination *c)
{
	int i;
	Destination * neighborsFound = NULL;

	for (i = 0; i < signed(c->neighbors.size()); i++)
	{
		if (x == c->x && y == c->y)
		{
			neighborsFound = c;
			break;
		}
	}
	if (neighborsFound == NULL)
	{
		neighborsFound = AddIfDestinationNotPresent(x, y);
		c->neighbors.push_back(neighborsFound);
	}
	return neighborsFound;
}
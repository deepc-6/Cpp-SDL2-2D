#pragma once

#include "Header.h"
#include "Destination.h"

typedef enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAXDIRECTION
}Direction;

class Path
{
private:	
	static void writeFile(std::string fileName);
	static void AnalyseLeftMovement(int x, int y, Destination *c);
	static void AnalyseRightMovement(int x, int y, Destination *c);
	static void AnalyseUpMovement(int x, int y, Destination *c);
	static void AnalyseDownMovement(int x, int y, Destination *c);
	static Destination * AddIfDestinationNotPresent(int x, int y);
	static Destination * AddIfNeighborsNotPresent(int x, int y, Destination *c);
	Direction findDirection(int frmx, int frmy, int tox, int toy);
	int findDistance(int frmx, int frmy, int tox, int toy);
public:
	Path();
	static Destination * findNeighbors(int x, int y);
	static void AnalysePathsFromCollision();
	int currentIndex;
	static std::vector<Destination *> *destinations;
	std::vector<Destination *> roadMap;
	void Guide(std::vector<Destination*> *destinations);
	void findPath(int x, int y);
};
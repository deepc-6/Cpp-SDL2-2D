#include "Destination.h"

Destination::Destination()
{
	currentStep = 0;
}

Destination::Destination(int x, int y, int d, int s)
{
	direction = d;
	numberOfSteps = s;

	this->x = x;
	this->y = y;

	currentStep = 0;
}

void Destination::Print()
{
	std::cout << "City " << x << ", " << y << " at numberOfSteps " << numberOfSteps << std::endl;

	for (Destination * neighbor : neighbors)
		std::cout << "\t Neighbour " << neighbor->x << ", " << neighbor->y << " at numberOfSteps " << neighbor->numberOfSteps << std::endl;
}

/*
bool Destination::operator==(const Destination &other) const
{
	if (other.x == this->x && other.y == this->y)
		return true;
	return false;
}
*/
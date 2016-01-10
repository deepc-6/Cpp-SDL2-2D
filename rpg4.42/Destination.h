#pragma once

#include "Header.h"

class Destination
{
public:
	Destination();
	Destination(int x, int y, int d, int s);
	std::vector<Destination *> neighbors;
	int x, y, direction, numberOfSteps, currentStep;
	void Print();
	//bool Destination::operator==(const Destination &other) const;
};
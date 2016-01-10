#include "StaticObjects.h"
#include "Main.h"

bool StaticObjects::InputWallFromFile(std::vector<AllObjects*> *wall)
{
	std::ifstream inFile;

	inFile.open("data/map.txt");
	if (!inFile)
	{
		std::cerr << "Cannot open input file" << std::endl;
		return false;
	}
	int column = 0;
	std::string str;
	std::string file_contents;
	while (std::getline(inFile, str))
	{
		int row = 0;
		for (char& c : str)
		{			
			if (c == WALL)
			{
				wall->push_back(new AllObjects("data/ground.bmp", row * GRANULARITY, column * GRANULARITY, 1, 1, WALL));
			}
			row++;
		}
		column++;
	}	
	inFile.close();
	return true;
}
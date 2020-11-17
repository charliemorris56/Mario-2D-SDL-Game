#include "LevelMap.h"

//When making a map, 0 = Empty Area & 1 = Blocked Area

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	mMap = new int* [MAP_WIDTH];
	for (unsigned int i = 0; i < MAP_WIDTH; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}

	//Populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//Delete all elements of the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] mMap[i];
	}
	delete[] mMap;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}
	return 0;
}

void LevelMap::ChangeTileAt(unsigned int h, unsigned int w, bool b)
{
	mMap[h][w] = b;
}
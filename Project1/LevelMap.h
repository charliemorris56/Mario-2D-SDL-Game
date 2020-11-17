#pragma once
#include "Constants.h"

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int h, unsigned int w, bool b);

private:
	int** mMap;
};


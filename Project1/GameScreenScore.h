#pragma once
#include "SDL.h"
#include "Commons.h"
#include "LevelMap.h"
#include "GameScreen.h"

class Texture2D;
class Character;
class PowBlock;

class GameScreenScore : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();

	void SetLevelMap();
	LevelMap* mLevelMap;

	float mBackgroundYPos;

public:
	GameScreenScore(SDL_Renderer* renderer);
	~GameScreenScore();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
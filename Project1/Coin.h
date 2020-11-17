#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D;

class Coin
{
public:
	Coin(SDL_Renderer* renderer, LevelMap* map, Vector2D postion);
	~Coin();

	void Render();

	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); };

	void TakeAHit();

	bool IsAvailable() { return mNumberOfHitsLeft > 0; };

	void Update(float deltaTime);

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mSpinTime;
	int mSpin;

	int mNumberOfHitsLeft;

};


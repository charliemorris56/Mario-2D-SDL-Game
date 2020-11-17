#pragma once
#include "Character.h"
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D;

class CharacterKoopa : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mInjuredTime;

	int health;

	bool mInjured;

	void FlipRightwayUp();
	
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();
	bool GetAlive();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
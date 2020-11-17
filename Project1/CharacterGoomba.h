#pragma once
#include "Character.h"
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D;

class CharacterGoomba : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mInjuredTime;

	int health;

	bool mInjured;

	void FlipRightwayUp();

public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterGoomba();

	void TakeDamage();
	void Jump();
	bool GetAlive();
	void SetAlive(bool alive);
	bool GetInjured();
	bool GetKillable();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};
#pragma once
#include "Character.h"
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D;

class CharacterMario :	public Character //TODO
{
private:


public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterMario();

	//void Render();
	void Update(float deltaTime, SDL_Event e);
};


#pragma once
#include "Character.h"
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D;

class CharacterLuigi :	public Character
{
private:

public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);
};


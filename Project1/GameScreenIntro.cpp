#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"

bool GameScreenIntro::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
		
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundIntro.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	mBackgroundYPos = 0.0f;

	return true;
}


GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenIntro::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
}
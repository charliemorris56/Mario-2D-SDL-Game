#include "GameScreenScore.h"

#include <iostream>
#include "Texture2D.h"

bool GameScreenScore::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundScore.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	mBackgroundYPos = 0.0f;

	return true;
}


GameScreenScore::GameScreenScore(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenScore::~GameScreenScore()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenScore::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
}

void GameScreenScore::Update(float deltaTime, SDL_Event e)
{
}
#include "GameScreenGameOver.h"
#include <iostream>
#include "Texture2D.h"

bool GameScreenGameOver::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundGO.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	mBackgroundYPos = 0.0f;

	return true;
}


GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenGameOver::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
}
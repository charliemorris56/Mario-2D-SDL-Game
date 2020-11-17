#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"
#include "GameScreenGameOver.h"
#include "GameScreenScore.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mCurrentScreen = NULL;
	mRenderer = renderer;

	//Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenLevel2* tempScreen2;
	GameScreenIntro* tempScreenIntro;
	GameScreenGameOver* tempScreenGameOver;
	GameScreenScore* tempScreenScore;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		tempScreenIntro = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenIntro;
		tempScreenIntro = NULL;
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen2;
		tempScreen2 = NULL;
		break;
	case SCREEN_GAMEOVER:
		tempScreenGameOver = new GameScreenGameOver(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenGameOver;
		tempScreenGameOver = NULL;
		break;
	case SCREEN_HIGHSCORES:
		tempScreenScore = new GameScreenScore(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenScore;
		tempScreenScore = NULL;
		break;
	default:
		break;
	}
}

//GameScreenManager* GameScreenManager::Instance()
//{
//	if (!mInstance)
//	{
//		mInstance = new GameScreenManager();
//	}
//
//	return mInstance;
//}
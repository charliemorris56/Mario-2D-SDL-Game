#include "GameScreenLevel2.h"
#include <iostream>
#include "Texture2D.h"

bool GameScreenLevel2::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);

	//Create the level map
	SetLevelMap();

	//Set up the player character
	myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(74, 330), mLevelMap);
	luigiCharacter = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(420, 331), mLevelMap);

	//Set up the POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	CreateGoomba(Vector2D(150, 10), FACING_RIGHT, KOOPA_SPEED);
	CreateGoomba(Vector2D(325, 10), FACING_LEFT, KOOPA_SPEED);

	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB2.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0 },
										{ 1,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);
}

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacter;
	myCharacter = NULL;
	delete luigiCharacter;
	luigiCharacter = NULL;
	mLevelMap = NULL;
	delete mPowBlock;
	delete goombaCharacter;
	goombaCharacter = NULL;
	mPowBlock = NULL;
	mEnemies.clear();
}

void GameScreenLevel2::Render()
{
	//Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	//Draw Mario
	myCharacter->Render();
	//Draw Luigi
	luigiCharacter->Render();
	//Draw Pow Block
	mPowBlock->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	myCharacter->Update(deltaTime, e); //TODO call the mario update here
	luigiCharacter->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//Collision detection
	/*if (Collision::Instance()->Circle(mCharacter1, mCharacter2))
	{

	}*/
	//if (Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mLugiCharacter->GetCollisionBox()))
	//{

	//}
}

void GameScreenLevel2::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(myCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (myCharacter->IsJumping())
			{
				DoScreenShake();

				mPowBlock->TakeAHit();
				myCharacter->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(luigiCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (luigiCharacter->IsJumping())
			{
				DoScreenShake();

				mPowBlock->TakeAHit();
				luigiCharacter->CancelJump();
			}
		}
	}
}

void GameScreenLevel2::DoScreenShake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	//Make the enemies take damage and shake
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		//Is the enemy on the bottom row
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{

			//Updates
			mEnemies[i]->Update(deltaTime, e);

			//Check if the player is above the enemy and then collides with the Goomba
			if (mEnemies[i]->GetPosition().y > myCharacter->GetPosition().y && Collisions::Instance()->Circle(mEnemies[i], myCharacter))
			{
				if (mEnemies[i]->GetInjured() && mEnemies[i]->GetKillable())
				{
					mEnemies[i]->SetAlive(false);
				}
				else 
				{
					mEnemies[i]->TakeDamage();
				}
			}
			else if (mEnemies[i]->GetPosition().y > luigiCharacter->GetPosition().y && Collisions::Instance()->Circle(mEnemies[i], luigiCharacter))
			{
				if (mEnemies[i]->GetInjured() && mEnemies[i]->GetKillable())
				{
					mEnemies[i]->SetAlive(false);
				}
				else
				{
					mEnemies[i]->TakeDamage();
				}
			}
			//Check enemy collides with player
			else if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignores the collisoin if the enemy is behind a pipe maybe??
			}
			else if (!mEnemies[i]->GetInjured())
			{
				if (Collisions::Instance()->Circle(mEnemies[i], myCharacter))
				{
					myCharacter->SetState(DEAD);
				}

				if (Collisions::Instance()->Circle(mEnemies[i], luigiCharacter))
				{
					luigiCharacter->SetState(DEAD);
				}
			}

			if (myCharacter->GetState() == DEAD && luigiCharacter->GetState() == DEAD)
			{
				//TODO Game Over
				//GameScreenManager gameScreenManager(nullptr, SCREEN_GAMEOVER);
				//GameScreenManager::Instance()->ChangeScreen(SCREEN_GAMEOVER);
			}

			//If the enemy is dead, send it for deletion
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	goombaCharacter = new CharacterGoomba(mRenderer, "Images/Goomba2.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(goombaCharacter);
}
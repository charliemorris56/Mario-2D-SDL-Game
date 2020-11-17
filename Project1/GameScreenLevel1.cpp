#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

bool GameScreenLevel1::SetUpLevel()
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

	//Set up the coin
	CreateCoin(Vector2D(75, 30));
	CreateCoin(Vector2D(420, 30));

	//Set up the Koopas
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacter;
	myCharacter = NULL;
	delete luigiCharacter;
	luigiCharacter = NULL;
	mLevelMap = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	delete koopaCharacter;
	koopaCharacter = NULL;
	delete mCoin;
	mCoin = NULL;
	mEnemies.clear();
	mCoins.clear();
}

void GameScreenLevel1::Render()
{
	//Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
	//Draw the Coins
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
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

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	myCharacter->Update(deltaTime, e);
	luigiCharacter->Update(deltaTime, e);
	UpdateCoin();
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime);
	}

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
}

void GameScreenLevel1::UpdatePOWBlock()
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

void GameScreenLevel1::UpdateCoin()
{
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		if (Collisions::Instance()->Box(myCharacter->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
		{
			if (mCoins[i]->IsAvailable())
			{
				mCoins[i]->TakeAHit();
			}
		}

		if (Collisions::Instance()->Box(luigiCharacter->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
		{
			if (mCoins[i]->IsAvailable())
			{
				mCoins[i]->TakeAHit();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
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

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		//Is the enemy on the bottom row
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Is the enemy off the screen left/right
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					//mEnemies[i]->SetAlive(false); //TODO
				}
			}

			//Updates
			mEnemies[i]->Update(deltaTime, e);

			//Check enemy collides with player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				
			}
			else
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	mCoin = new Coin(mRenderer, mLevelMap, position);
	mCoins.push_back(mCoin);
}
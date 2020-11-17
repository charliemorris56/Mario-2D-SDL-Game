#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, LevelMap* map, Vector2D position)
{
	std::string imagePath = "Images/Coin.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}

	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 1;
	mPosition = position;

	mRenderer = renderer;

	mSpinTime = COIN_SPEED;
	mSpin = 0;
}


Coin::~Coin()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void Coin::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		int left = mSingleSpriteWidth * mSpin;
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

void Coin::Update(float deltaTime)
{
	mSpinTime -= deltaTime;

	if (mSpinTime > (COIN_SPEED / 3) * 2)
	{
		mSpin = 1;
	}
	else if (mSpinTime > COIN_SPEED / 3)
	{
		mSpin = 2;
	}
	else if (mSpinTime > 0)
	{
		mSpin = 0;
	}
	else if (mSpinTime <= 0.0)
	{
		mSpinTime = COIN_SPEED - deltaTime;		
	}
}


void Coin::TakeAHit()
{
	mNumberOfHitsLeft--;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;

		mPosition = Vector2D((SCREEN_WIDTH * 0.25f) - mSingleSpriteWidth * 0.5f, -20);
	}
}
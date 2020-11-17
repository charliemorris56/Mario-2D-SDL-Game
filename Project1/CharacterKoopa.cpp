#include "CharacterKoopa.h"

void CharacterKoopa::FlipRightwayUp()
{
	if (mFacingDirection == FACING_LEFT)
	{
		mFacingDirection = FACING_RIGHT;
	}
	else
	{
		mFacingDirection = FACING_LEFT;
	}

	mInjured = false;
	Jump();
}

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();

	mInjuredTime = INJURED_TIME;
	
	health = 2; //TODO
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();

	//health--; //TODO
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

bool CharacterKoopa::GetAlive()
{
	if (health == 0)
	{
		return false;
	}	

	return true;	
}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mInjured)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mPosition.x -= mMovementSpeed * deltaTime;
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mPosition.x += mMovementSpeed * deltaTime;
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		mMovingRight = false;
		mMovingLeft = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
		{
			FlipRightwayUp();
		}
	}

	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	//if travling right and then next tile at the foot and to the right is air turn around
	if (mMovingRight && mCurrentLevelMap->GetTileAt(footPosition + 1, centralXPosition) == 0) //TODO fix this
	{
		mFacingDirection = FACING_LEFT;
	}
	else if (mMovingLeft && mCurrentLevelMap->GetTileAt(footPosition + 1, centralXPosition) == 0)
	{
		mFacingDirection = FACING_RIGHT;
	}
}
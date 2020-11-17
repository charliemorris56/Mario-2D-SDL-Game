#include "CharacterGoomba.h"

void CharacterGoomba::FlipRightwayUp()
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

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight() / 3;

	mInjuredTime = INJURED_TIME;

	health = 2;
}

CharacterGoomba::~CharacterGoomba()
{
}

void CharacterGoomba::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterGoomba::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

bool CharacterGoomba::GetAlive()
{
	if (health == 0)
	{
		return false;
	}

	return true;
}

void CharacterGoomba::SetAlive(bool alive)
{
	if (!alive)
	{
		health = 0;
	}
}

bool CharacterGoomba::GetInjured()
{
	if (mInjured)
	{
		return true;
	}

	return false;	
}

bool CharacterGoomba::GetKillable()
{
	if (mInjuredTime <= 1.0f)
	{
		return true;
	}

	return false;
}

void CharacterGoomba::Render()
{
	int left = 0.0f;

	if (mInjured)
	{
		left = mSingleSpriteWidth * 2;
	}

	SDL_Rect portionOfSpritesheet = { 0, left, mSingleSpriteWidth, mSingleSpriteHeight };

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

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
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
	int footPosition = (int)(mPosition.y + (mTexture->GetHeight() * 0.33f)) / TILE_HEIGHT;

	//Deal with gravity
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)// == 0 && mGravityOn
	{
		//In the air with gravity on
		AddGravity(deltaTime);
	}
	else
	{
		//Collided with ground so we can jump again
		mCanJump = true;
	}

	if (mCanJump && mMovingRight && mCurrentLevelMap->GetTileAt(footPosition + -1, centralXPosition) == 1)
	{
		mFacingDirection = FACING_LEFT;
	}
	else if (mCanJump && mMovingLeft && mCurrentLevelMap->GetTileAt(footPosition - 1, centralXPosition) == 1)
	{
		mFacingDirection = FACING_RIGHT;
	}

	//if travling right and then next tile at the foot and to the right is air turn around
	//if (mMovingRight && mCurrentLevelMap->GetTileAt(footPosition + 1, centralXPosition) == 0) //TODO fix this
	//{
	//	mFacingDirection = FACING_LEFT;
	//}
	//else if (mMovingLeft && mCurrentLevelMap->GetTileAt(footPosition + 1, centralXPosition) == 0)
	//{
	//	mFacingDirection = FACING_RIGHT;
	//}
}
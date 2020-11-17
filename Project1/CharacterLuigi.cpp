#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mPosition = startPosition;
}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	if (mJumping) //TODO add mCanJump
	{
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}

	switch (e.type)
	{
	case SDL_KEYDOWN: //Pressing the key down
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingRight = true;
			break;
		default:
			break;
		}
	default:
		break;
	}

	switch (e.type)
	{
	case SDL_KEYUP: //Releasing the key up
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		default:
			break;
		}
	default:
		break;
	}

	//Jumping
	switch (e.type)
	{
	case SDL_KEYDOWN: //Releasing the key down
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump(deltaTime);
			break;
		default:
			break;
		}
	default:
		break;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	//Collision position variable
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

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
}
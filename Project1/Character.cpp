#include "Character.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_LEFT;
	mState = ALIVE;

	mMovingLeft = false;
	mMovingRight = false;
	mCanJump = false;
	mGravityOn = true;
	mJumping = false;
	currentlyJumping = false; //TODO remove this
	mJumpForce = INITIAL_JUMP_FORCE;

	mCollisionRadius = 15.0f;

	mCurrentLevelMap = map;

	//mJumpTime = 0.25f;
	mCurrentYPos = 0.0f;

	mMovementSpeed = 50.0f;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	//mTexture->Render(mPosition, SDL_FLIP_NONE, 0);

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
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

	//mPosition.x += 10;
	switch (e.type)
	{
	case SDL_KEYDOWN: //Pressing the key down
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
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
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		default:
			break;
		}
	default:
		break;
	}

	//currentlyJumping = false;
	//Jumping
	switch (e.type)
	{
	case SDL_KEYDOWN: //Releasing the key down
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
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

void Character::setPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x -= mMovementSpeed * deltaTime;
	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += mMovementSpeed * deltaTime;
	mFacingDirection = FACING_RIGHT;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

void Character::AddGravity(float deltaTime)
{
	if (!currentlyJumping)
	{
		mPosition.y += GRAVITY * deltaTime;
		mCanJump = false;
	}
}

void Character::Jump(float deltaTime)
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

bool Character::IsJumping()
{
	return mJumping;
}

void Character::CancelJump()
{
	mJumping = false;
}

void Character::SetState(STATE state)
{
	mState = state;

	if (mState == DEAD)
	{
		mPosition.x = -100.0f;
		mPosition.y = -100.0f;
	}
}

STATE Character::GetState()
{
	return mState;
}

#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
}

CharacterMario::~CharacterMario()
{
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
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

		//mJumpTime -= deltaTime;
		//Jump(deltaTime);
		//
		//if (mJumpTime <= 0.0f)
		//{
		//	CancelJump();
		//mJumpTime = 0.25;
		//	//mCanJump = false;
		//	std::cout <<" test";
		//}
		//if (IsJumping())
		//{
		//	while (mJumpTime >= 0.0f)
		//	{
		//		gravityOn = false;
		//		mJumpTime -= deltaTime;
		//		Jump(deltaTime);
		//		std::cout << mJumpTime;
		//
		//		if (mJumpTime <= 0.0f)
		//		{
		//			CancelJump();
		//			//mJumpTime = 0.25;
		//			//mCanJump = false;
		//			std::cout << " test";
		//			gravityOn = true;
		//		}
		//	}
		//}
	}
	else
	{
		//Collided with ground so we can jump again
		mCanJump = true;
	}
	//else if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0 && !gravityOn)
	//{
	//	//In the air with gravity off, i.e. currenlty doing a jump
	//	mJumpTime = 1.25;
	//	//	//mCanJump = false;
	//	//	std::cout <<" test";
	//	//}
	//	
	//	
	//		//gravityOn = false;
	//		mJumpTime -= deltaTime;
	//		Jump(deltaTime);
	//		std::cout << mJumpTime;
	//
	//		if (mJumpTime <= 0.0f)
	//		{
	//			CancelJump();
	//			//mJumpTime = 0.25;
	//			//mCanJump = false;
	//			std::cout << " test";
	//			gravityOn = true;
	//		}
	//
	//	
	//}

}

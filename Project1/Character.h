#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D;

class Character
{
private:

protected:
	FACING mFacingDirection;
	STATE mState;

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	float mCollisionRadius;		
	float mMovementSpeed;

	bool mMovingLeft;
	bool mMovingRight;
	bool mCanJump;
	bool mJumping;
	float mJumpForce;
	bool currentlyJumping;
	bool mGravityOn;

	LevelMap* mCurrentLevelMap;

	//float mJumpTime;
	float mCurrentYPos;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void setPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox() 	{return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());}

	void AddGravity(float deltaTime);
	void Jump(float deltaTime);

	bool IsJumping();
	void CancelJump();

	void SetState(STATE state);
	STATE GetState();
};
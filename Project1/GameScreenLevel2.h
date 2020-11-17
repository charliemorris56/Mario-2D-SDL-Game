#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Collisions.h"
#include "CharacterKoopa.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterGoomba.h"
#include <vector>

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel2 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();

	Character* myCharacter;
	CharacterGoomba* goombaCharacter;
	CharacterLuigi* luigiCharacter;

	void SetLevelMap();
	LevelMap* mLevelMap;

	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	std::vector<CharacterGoomba*> mEnemies;

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdatePOWBlock();

	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateGoomba(Vector2D position, FACING direction, float speed);
};
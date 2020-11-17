#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Coin.h"
#include "Collisions.h"
#include "CharacterKoopa.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include <vector>

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();

	Character* myCharacter;
	CharacterKoopa* koopaCharacter;
	CharacterLuigi* luigiCharacter;

	void SetLevelMap();
	LevelMap* mLevelMap;

	PowBlock* mPowBlock;

	Coin* mCoin;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	std::vector<CharacterKoopa*> mEnemies;

	std::vector<Coin*> mCoins;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdatePOWBlock();
	void UpdateCoin();

	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void CreateCoin(Vector2D position);
};
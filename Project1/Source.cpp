#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Texture2D* gTexture = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
Mix_Music* gMusic = NULL;

//Function Prototypes
bool InitSDL();
void CloseSLD();
bool Update();
void Render();
void LoadMusic(string path);
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();

int main(int argc, char* args[])	
{
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		//Set up the game screen manager - Start with Level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
		gOldTime = SDL_GetTicks();
		
		//Pause for a few seconds
		//SDL_Delay(5000);
	}

	//Flag to check if we wish to quit
	bool  quit = false;

	//Game Loop
	while (!quit)
	{
		Render();
		quit = Update();
	}

	//Close Window and free resources
	CloseSLD();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "DSL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good, so attempt to create the window
		gWindow = SDL_CreateWindow("Game Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}

		//Initialise the Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error " << Mix_GetError();
			return false;
		}

		//Load the background texture
		//gTexture = new Texture2D(gRenderer);
		//if (!gTexture->LoadFromFile("Images/test.bmp"))
		//{
		//	return false;
		//}

		//Did the window get created?
		if (gWindow == NULL)
		{
			//No
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		else //Yes
		{
			return true;
		}
	}
}

void CloseSLD()
{
	//Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Clear up the texture
	//delete gTexture;
	//gTexture = NULL;

	//Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//Destory the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;
}

bool Update()
{
	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;
	
	//Get the events
	SDL_PollEvent(&e);

	//Handle any events
	switch (e.type)
	{
		//Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	//Set the current time to be the old time
	gOldTime = newTime;

	//Update the level
	switch (e.type)
	{
	case SDL_KEYDOWN: //Pressing the key down
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
			Mix_FreeMusic(gMusic);
			LoadMusic("Music/Mario.mp3");
			break;
		case SDLK_l:
			gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
			Mix_FreeMusic(gMusic);
			LoadMusic("Music/MarioUnderworld.mp3");
			break;
		case SDLK_k:
			gameScreenManager->ChangeScreen(SCREEN_GAMEOVER);
			break;
		case SDLK_j:
			gameScreenManager->ChangeScreen(SCREEN_HIGHSCORES);
			break;
		default:
			break;
		}
	default:
		break;
	}

	return false;
}

void Render()
{
	//Clear the screen - Black
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	//gTexture->Render(Vector2D(), SDL_FLIP_NONE);
	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}
}

/*SDL_Texture* LoadTextureFromFile(string path)
{
	//Remove the memory used for a previous texture
	FreeTexture();
	SDL_Texture* pTexture = NULL;

	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Create the texture from the pixels in the surface
		pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
		if (pTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
	}

	//Remove the loaded surface now that we have the texture
	SDL_FreeSurface(pSurface);

	//Retirn the texture
	return pTexture;
}*/

/*void FreeTexture()
{
	//Check if the texture exists before removing it
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
}*/
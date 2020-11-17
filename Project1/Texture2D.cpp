#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	//mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D()
{
	//Free up the memory
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string path)
{
	//Remove the memory used for a previous texture
	Free();

	//Load the image
	SDL_Surface* mSurface = IMG_Load(path.c_str());
	if (mSurface != NULL)
	{
		//Create the texture from the pixels in the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		//Set the dimensions
		mWidth = mSurface->w;
		mHeight = mSurface->h;

		SDL_SetColorKey(mSurface, SDL_TRUE, SDL_MapRGB(mSurface->format, 0, 0xFF, 0xFF));

		//Remove the loaded surface now that we have the texture
		SDL_FreeSurface(mSurface);

	}
	else
	{
		cout << "Unable to create texture from surface......" << IMG_GetError() << "\n";
	}

	

	//Return the texture
	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Clear the screen
	//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(mRenderer);

	//Set where to render the texture
	SDL_Rect renderLocaiton = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocaiton, 0, NULL, flip);

	//Update the screen
	//SDL_RenderPresent(mRenderer);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

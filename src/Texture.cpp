#include "Texture.hpp"
Texture::Texture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();
	SDL_Surface *textSurface = TTF_RenderText_Solid(fGameOver, textureText.c_str(), textColor);
	if (textSurface == NULL)
		std::cout << "Khong the tao khong gian ve! SDL_ttf Error: " << TTF_GetError() << std::endl;
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
			std::cout << "Khong ve duoc chu len man hinh! SDL Error: " << SDL_GetError() << std::endl;
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Xoa hinh anh cu
		SDL_FreeSurface(textSurface);
	}

	// Tra ve thanh cong
	return mTexture != NULL;
}

bool Texture::loadFromFile(std::string path)
{
	free();
	SDL_Texture *newTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		std::cout << "Khong the load anh! SDL_image error: " << IMG_GetError() << std::endl;
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
			std::cout << "Khong ve duoc anh tai " << path << "! SDL error: " << SDL_GetError() << std::endl;
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void Texture::free()
{
	if (mTexture == NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect *clip)
{
	SDL_Rect rect = {x, y, mWidth, mHeight};

	if (clip != NULL)
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopy(renderer, mTexture, clip, &rect);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

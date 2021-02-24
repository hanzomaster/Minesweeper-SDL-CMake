#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
class Texture
{
public:
	Texture();

	~Texture();

	// Tao anh tu font
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	// Tai anh tu duong dan
	bool loadFromFile(std::string path);

	void free();

	// Vi tri tao text
	void render(int x, int y, SDL_Rect* clip = NULL);

	// Lay vi tri anh
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;

	// Vi tri anh
	int mWidth;
	int mHeight;
};


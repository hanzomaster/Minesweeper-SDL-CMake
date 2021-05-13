#pragma once
#include <string>
class Texture
{
public:
	Texture();

	~Texture();

	// Tạo ảnh từ font
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	// Tải ảnh từ đường dẫn
	bool loadFromFile(std::string path);

	void free();

	// Tạo text tại vị trí bất kì
	void render(int x, int y, SDL_Rect *clip = NULL);

	// Lấy vị trí ảnh
	int getWidth();
	int getHeight();
	SDL_Rect getRect() const;

private:
	SDL_Texture *mTexture;

	// Vị trí ảnh
	SDL_Rect rect;
	int mWidth;
	int mHeight;
};

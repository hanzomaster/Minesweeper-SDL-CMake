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

private:
	SDL_Texture *mTexture;

	// Vị trí ảnh
	int mWidth;
	int mHeight;
};

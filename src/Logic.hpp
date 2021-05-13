#pragma once
#include <SDL.h>

#include <utility>
#include <vector>
class Button {
public:
	void reveal(int i, int j);

	bool correctFlag(int i, int j);

	void revealSurrounding(int i, int j);

	// Khởi tạo vị trí
	void setPosition(int x, int y);

	// Nhận phản hồi từ chuột
	void handleEvents(SDL_Event *event);

	// Đưa ra màn hình
	void render(int i, int j);

private:
	SDL_Point mPosition;
};

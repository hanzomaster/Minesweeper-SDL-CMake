#pragma once
#include <SDL.h>
#include <vector>
#include <utility>
class Button
{
public:
	void reveal(int i, int j);

	bool correctFlag(int i, int j);

	void revealSurrounding(int i, int j);

	//Khoi tao vi tri
	void setPosition(int x, int y);

	//Nhan phan hoi tu chuot cua nguoi dung
	void handleEvents(SDL_Event *e);

	//Dua ra man hinh
	void render(int i, int j);

private:
	SDL_Point mPosition;
	std::vector<std::pair<int, int>> surroundPos;
};

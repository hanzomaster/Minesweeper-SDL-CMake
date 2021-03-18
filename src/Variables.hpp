#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>
#include "Texture.hpp"

// Kích cỡ một ô mìn
const int CELL_SIZE = 32;
const int BUTTON_SPRITE_TOTAL = 12;

// Biến window và kích cỡ
extern SDL_Window *window;
extern int screenWidth;
extern int screenHeight;

// The window renderer
extern SDL_Renderer *renderer;

// Các font chữ trong game
extern TTF_Font *fGame;

// Mouse button texture
extern SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
extern Texture buttonSpriteSheetTexture;

// Biến in ra chữ trong game
extern Texture gGameOver;
extern Texture gMineLeftTexture;
extern Texture gPlayAgainTexture;
extern Texture gWin;

// Tổng số mìn
extern int numOfMine;

// Kích cỡ sân mìn
extern int rowSize;
extern int columnSize;

// Biến trò chơi
extern int countMineLeft;
extern bool gameOver;
extern bool isWinning;
extern std::stringstream mineLeft;

enum title
{
	MINE = 9,
	COVER,
	FLAG
};

enum gameModeSelect
{
	Easy,
	Medium
};

enum menuSelect
{
	NewGame,
	Exit,
	Back,
	Quit
};

// Vị trí sân mìn
extern int DISTANCE_BETWEEN;

// Sân mìn mẫu
extern std::vector<std::vector<int>> board;

// Sân mìn người chơi sẽ tương tác
extern std::vector<std::vector<int>> sBoard;
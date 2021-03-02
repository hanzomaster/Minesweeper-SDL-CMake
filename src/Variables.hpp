#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>
#include "Texture.hpp"

//Cell's constants
const int CELL_SIZE = 32;
const int BUTTON_SPRITE_TOTAL = 12;

// The window we'll be rendering to
extern SDL_Window *window;
extern int screenWidth;
extern int screenHeight;

// The window renderer
extern SDL_Renderer *renderer;

// Globally used font
extern TTF_Font *fGameOver;
extern TTF_Font *fPlayAgain;
extern TTF_Font *fWin;

// Mouse button texture
extern SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
extern Texture buttonSpriteSheetTexture;

// Screen texture
extern Texture gWinningTexture;

// Rendered texture
extern Texture gGameOver;
extern Texture gMineLeftTexture;
extern Texture gPlayAgainTexture;
extern Texture gWin;

// Gameplay variables
extern int countMineLeft;
extern int countCellLeft;
extern bool gameOver;
extern bool isWinning;

// In memory text stream
extern std::stringstream mineLeft;

// Size of the board
extern int rowSize;
extern int columnSize;

// Number of mine
extern int numOfMine;
enum title
{
	MINE = 9,
	COVER,
	FLAG
};

// Screen dimension
extern int DISTANCE_BETWEEN;

// Board with mine
extern std::vector<std::vector<int>> board;

// Board for showing
extern std::vector<std::vector<int>> sBoard;

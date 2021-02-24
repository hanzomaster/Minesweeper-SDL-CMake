#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>
#include <utility>
#include "Texture.hpp"
#include "Button.hpp"
//Tile's constants
const int TILE_SIZE = 32;
const int BUTTON_SPRITE_TOTAL = 12;

// The window we'll be rendering to
extern SDL_Window* gWindow;
extern int screenWidth;
extern int screenHeight;

// The window renderer
extern SDL_Renderer* renderer;

// Globally used font
extern TTF_Font* fGameOver;
extern TTF_Font* fPlayAgain;
extern TTF_Font* fWin;

// Mouse button texture
extern SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
extern Texture gButtonSpriteSheetTexture;

// Screen texture
extern Texture gWinningTexture;

// Rendered texture
extern Texture gGameOver;
extern Texture gMineLeftTexture;
extern Texture gPlayAgainTexture;
extern Texture gWin;

// Gameplay variables
extern int countMineLeft;
extern int countTileLeft;
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


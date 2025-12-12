#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <vector>
#include "Texture.hpp"
#include "Logic.hpp"

// Frame rate limiting
constexpr int FPS = 24;
constexpr int frameDelay = 1000 / FPS;
extern Uint32 frameStart;
extern unsigned int frameTime;

// Cell and sprite constants
constexpr int CELL_SIZE = 32;
constexpr int BUTTON_SPRITE_TOTAL = 13;

// Screen dimensions
constexpr int MENU_SCREEN_WIDTH = 500;
constexpr int MENU_SCREEN_HEIGHT = 500;
constexpr int EASY_SCREEN_WIDTH = 500;
constexpr int EASY_SCREEN_HEIGHT = 500;
constexpr int MEDIUM_SCREEN_WIDTH = 800;
constexpr int MEDIUM_SCREEN_HEIGHT = 800;
constexpr int HARD_SCREEN_WIDTH = 1024;
constexpr int HARD_SCREEN_HEIGHT = 576;

// Difficulty settings
constexpr int EASY_ROWS = 9;
constexpr int EASY_COLS = 9;
constexpr int EASY_MINES = 10;
constexpr int MEDIUM_ROWS = 16;
constexpr int MEDIUM_COLS = 16;
constexpr int MEDIUM_MINES = 40;
constexpr int HARD_ROWS = 16;
constexpr int HARD_COLS = 30;
constexpr int HARD_MINES = 99;

// UI layout constants
constexpr int MENU_ITEM_SPACING = 60;
constexpr int TEXT_Y_OFFSET = 30;
constexpr int FONT_SIZE = 40;

// Common colors (const instead of constexpr for aggregate initialization compatibility)
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_RED = {255, 0, 0, 255};
const SDL_Color COLOR_GRAY = {140, 140, 140, 255};
const SDL_Color COLOR_DARK_GRAY = {100, 100, 100, 255};
const SDL_Color COLOR_TEAL = {30, 100, 100, 255};
const SDL_Color COLOR_GOLD = {255, 215, 0, 255};
const SDL_Color COLOR_BACKGROUND = {204, 204, 204, 255};

// Biến window và kích cỡ
extern SDL_Window *window;
extern int screenWidth;
extern int screenHeight;

// The window renderer
extern SDL_Renderer *renderer;

// Font chữ trong game
extern TTF_Font *fGame;

// Biến để cắt ảnh các ô số và mìn
extern SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
extern Texture buttonSpriteSheetTexture;

// Biến in ra chữ trong game
extern Texture gGameOver;
extern Texture gMineLeftTexture;
extern Texture gPlayAgainTexture;
extern Texture gWin;

// Biến âm thanh trong game
extern Mix_Chunk *menuClick;
extern Mix_Chunk *openCell;
extern Mix_Chunk *flag;
extern Mix_Chunk *unFlag;
extern Mix_Chunk *mineFounded;
extern Mix_Music *winning;
extern Texture gameSound;
extern bool isMute;

// Tổng số mìn
extern int numOfMine;

// Kích cỡ sân mìn
extern int rowSize;
extern int columnSize;

// Biến trò chơi
extern int countMineLeft;
extern bool gameOver;
extern bool isWinning;
extern bool isFirstClick;
extern std::stringstream mineLeft;

enum title
{
	BLANK,
	MINE = 9,
	COVER,
	FLAG,
	QUESTION
};

enum gameModeSelect
{
	Easy,
	Medium,
	Hard
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
extern std::vector<std::vector<Button>> gButtons;

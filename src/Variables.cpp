#include "Variables.hpp"

//Cell's constants
extern const int CELL_SIZE;
extern const int BUTTON_SPRITE_TOTAL;

//The window we'll be rendering to
SDL_Window *window;
int screenWidth = 500;
int screenHeight = 500;

//The window renderer
SDL_Renderer *renderer;

//Globally used font
TTF_Font *fGameOver;
TTF_Font *fPlayAgain;
TTF_Font *fWin;

//Mouse button texture
SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
Texture buttonSpriteSheetTexture;

//Rendered texture
Texture gGameOver;
Texture gMineLeftTexture;
Texture gPlayAgainTexture;
Texture gWin;
Texture gWinningTexture;

//Gameplay variables
int countMineLeft = numOfMine;
int countCellLeft;
bool gameOver;
bool isWinning;
std::stringstream mineLeft;

// Size of the board
int rowSize = 10;
int columnSize = 10;

//Number of mine
int numOfMine = 12;

// Screen dimension
int DISTANCE_BETWEEN = (screenWidth - rowSize * CELL_SIZE - 50) / 2;

//Board with mine
std::vector<std::vector<int>> board(rowSize + 2, std::vector<int>(columnSize + 2, 0));

//Board for showing
std::vector<std::vector<int>> sBoard(rowSize + 2, std::vector<int>(columnSize + 2, COVER));

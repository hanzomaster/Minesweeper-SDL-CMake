#include "Variables.hpp"

//Tile's constants
extern const int TILE_SIZE;
extern const int BUTTON_SPRITE_TOTAL;

//The window we'll be rendering to
SDL_Window *gWindow;
int screenWidth = 500;
int screenHeight = 500;

//The window renderer
SDL_Renderer *renderer;

//Globally used font
TTF_Font *fGameOver;
TTF_Font *fPlayAgain;
TTF_Font *fWin;

//Mouse button texture
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
Texture gButtonSpriteSheetTexture;

//Screen texture
Texture gWinningTexture;

//Rendered texture
Texture gGameOver;
Texture gMineLeftTexture;
Texture gPlayAgainTexture;
Texture gWin;

//Gameplay variables
int countMineLeft = numOfMine;
int countTileLeft;
bool gameOver;
bool isWinning;

//In memory text stream
std::stringstream mineLeft;

// Size of the board
int rowSize = 10;
int columnSize = 10;

//Number of mine
int numOfMine = 12;

// Screen dimension
int DISTANCE_BETWEEN = (screenWidth - rowSize * TILE_SIZE) / 2;

//Board with mine
std::vector<std::vector<int>> board(rowSize + 2, std::vector<int>(columnSize + 2, 0));

//Board for showing
std::vector<std::vector<int>> sBoard(rowSize + 2, std::vector<int>(columnSize + 2, COVER));

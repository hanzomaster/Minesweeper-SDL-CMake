#include "Variables.hpp"

// Kích cỡ một ô mìn
extern const int CELL_SIZE;
extern const int BUTTON_SPRITE_TOTAL;

// Biến window và kích cỡ
SDL_Window *window;
int screenWidth = rowSize * 50;
int screenHeight = columnSize * 50;

// The window renderer
SDL_Renderer *renderer;

// Các font chữ trong game
TTF_Font *fGameOver;
TTF_Font *fPlayAgain;
TTF_Font *fWin;

// Mouse button texture
SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
Texture buttonSpriteSheetTexture;

// Biến in ra chữ trong game
Texture gGameOver;
Texture gMineLeftTexture;
Texture gPlayAgainTexture;
Texture gWin;

// Tổng số mìn
int numOfMine = 12;

// Kích cỡ sân mìn
int rowSize = 10;
int columnSize = 10;

// Biến trò chơi
int countMineLeft = numOfMine;
bool gameOver = false;
bool isWinning = false;
std::stringstream mineLeft;

// Vị trí sân mìn
int DISTANCE_BETWEEN = (screenWidth - rowSize * CELL_SIZE - 50) / 2;

// Sân mìn mẫu
std::vector<std::vector<int>> board(rowSize + 2, std::vector<int>(columnSize + 2, 0));

// Sân mìn người chơi sẽ tương tác
std::vector<std::vector<int>> sBoard(rowSize + 2, std::vector<int>(columnSize + 2, COVER));

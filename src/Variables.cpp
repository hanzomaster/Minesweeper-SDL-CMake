#include "Variables.hpp"

// Giới hạn fps
extern const int FPS;
extern const int frameDelay;
Uint32 frameStart;
unsigned int frameTime;

// Kích cỡ một ô mìn
extern const int CELL_SIZE;
extern const int BUTTON_SPRITE_TOTAL;

// Biến window và kích cỡ
SDL_Window *window;
int screenWidth = 500;
int screenHeight = 500;

// The window renderer
SDL_Renderer *renderer;

// Font chữ trong game
TTF_Font *fGame;

// Biến để cắt ảnh các ô số và mìn
SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
Texture buttonSpriteSheetTexture;

// Biến in ra chữ trong game
Texture gGameOver;
Texture gMineLeftTexture;
Texture gPlayAgainTexture;
Texture gWin;

// Biến âm thanh trong game
Mix_Chunk *menuClick;
Mix_Chunk *openCell;
Mix_Chunk *flag;
Mix_Chunk *unFlag;
Mix_Chunk *mineFounded;
Mix_Music *winning;
Texture gameSound;
bool isMute;

// Tổng số mìn
int numOfMine;

// Kích cỡ sân mìn
int rowSize = 9;
int columnSize = 9;

// Biến trò chơi
int countMineLeft;
bool gameOver = false;
bool isWinning = false;
std::stringstream mineLeft;

// Vị trí sân mìn
int DISTANCE_BETWEEN;

// Sân mìn mẫu
std::vector<std::vector<int>> board(rowSize + 2, std::vector<int>(columnSize + 2, 0));

// Sân mìn người chơi sẽ tương tác
std::vector<std::vector<int>> sBoard(rowSize + 2, std::vector<int>(columnSize + 2, COVER));
std::vector<std::vector<Button>> gButtons(rowSize + 2, std::vector<Button>(columnSize + 2));

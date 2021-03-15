#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Variables.hpp"
#include "Texture.hpp"
#include "Button.hpp"
#include "StartScreen.hpp"

std::vector<std::vector<Button>> gButtons(rowSize + 2, std::vector<Button>(columnSize + 2));
bool init();
std::string getSourcesPath();
bool loadMedia();
void resizeBoard(int rowSize, int columnSize);
void createTableWithMine();
bool checkWinning();
void mineManager();
void flagManager();
void playAgain(bool &quitGame);
void close();
int main(int argc, char *argv[])
{
	// BUG: Số hàng và cột của bàn mìn không thể lên được 14
	if (!init())
		std::cout << "Khoi tao chuong trinh that bai..." << std::endl;
	else if (!loadMedia())
		std::cout << "Khoi tao phong chu that bai..." << std::endl;
	else
	{
		int menuOption = showMenu();
		switch (menuOption)
		{
		case NewGame:
		{
			int gameModeOption = showGameMode();
			switch (gameModeOption)
			{
			case Easy:
			{
				numOfMine = 10;
				rowSize = 9;
				columnSize = 9;
				resizeBoard(rowSize, columnSize);
				break;
			}
			case Medium:
			{
				numOfMine = 25;
				rowSize = 13;
				columnSize = 13;
				resizeBoard(rowSize, columnSize);
				break;
			}
			}
			bool quit = false;
			SDL_Event event;
			createTableWithMine();
			// Vòng lặp của game
			while (!quit)
			{
				while (!gameOver && !quit && !isWinning)
				{
					// Xử lí các thao tác
					while (SDL_PollEvent(&event) != 0)
					{
						if (event.type == SDL_QUIT)
							quit = true;
						else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
							quit = true;
						for (int i = 1; i <= rowSize; ++i)
							for (int j = 1; j <= columnSize; ++j)
								gButtons[i][j].handleEvents(&event);
						isWinning = checkWinning();
					}

					// Tạo background
					SDL_RenderClear(renderer);

					// Vẽ sân mìn
					for (int i = 1; i <= rowSize; ++i)
						for (int j = 1; j <= columnSize; ++j)
							gButtons[i][j].render(i, j);

					mineManager();

					flagManager();

					SDL_RenderPresent(renderer);
				}
				playAgain(quit);
			}
		}
		break;
		case Exit:
			break;
		}
	}
	close();
	return 0;
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Khong the khoi tao SDL. Loi: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			std::cout << "Loc tuyen tinh khong duoc khoi dong" << std::endl;

		window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Khong the tao cua so game! SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				std::cout << "Khong the tao but ve! SDL error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				{
					std::cout << "Khong the khoi dong SDL_image! SDL_image error: " << IMG_GetError() << std::endl;
					success = false;
				}
				if (TTF_Init() == -1)
				{
					std::cout << "Khong the khoi dong SDL_ttf! SDL_ttf error: " << TTF_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}

std::string getSourcesPath()
{
	std::string baseRes;
	char *basePath = SDL_GetBasePath();
	if (basePath)
	{
		baseRes = basePath;
		SDL_free(basePath);
	}
	int pos = baseRes.find("build");
	baseRes = baseRes.substr(0, pos) + "src/";
	for (int i = 0; i < baseRes.length(); ++i)
		if (baseRes[i] == '\\')
			baseRes[i] = '/';
	return baseRes;
}

bool loadMedia()
{
	bool success = true;
	std::string resPath = getSourcesPath();
	std::string fontPath = resPath + std::string("Font/visitor1.ttf");
	std::string imgPath = resPath + std::string("Images/Cells.png");
	// Tạo màu background
	SDL_SetRenderDrawColor(renderer, 204, 204, 204, 255);

	// Tạo các font chữ sẽ hiện lên màn hình
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
	if (fGame == NULL)
	{
		std::cout << "Khong the mo font visitor1! SDL_ttf error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!gGameOver.loadFromRenderedText("GAME OVER", {140, 140, 140}))
		{
			std::cout << "Khong the tao text!" << std::endl;
			success = false;
		}
		if (!gWin.loadFromRenderedText("You Win", {140, 140, 140}))
		{
			std::cout << "Khong the tao text!" << std::endl;
			success = false;
		}
		if (!gPlayAgainTexture.loadFromRenderedText("Press s to play again!", {30, 100, 100}))
		{
			std::cout << "Khong the tao text!" << std::endl;
			success = false;
		}
	}

	// Cắt các ô mìn từ hình ảnh Cells.png
	if (!buttonSpriteSheetTexture.loadFromFile(imgPath.c_str()))
	{
		std::cout << "Khong the load cac o min" << std::endl;
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			spriteClips[i].x = i * CELL_SIZE;
			spriteClips[i].y = 0;
			spriteClips[i].w = CELL_SIZE;
			spriteClips[i].h = CELL_SIZE;
		}
	}
	return success;
}

void resizeBoard(int rowSize, int columnSize)
{
	board.resize(rowSize + 2, std::vector<int>(columnSize + 2, 0));
	sBoard.resize(rowSize + 2, std::vector<int>(columnSize + 2, COVER));
	gButtons.resize(rowSize + 2, std::vector<Button>(columnSize + 2));
	countMineLeft = numOfMine;
	DISTANCE_BETWEEN = (screenWidth - (rowSize + 2) * CELL_SIZE) / 2;
	// Tạo vị trí các ô
	for (int i = 1; i <= rowSize; ++i)
		for (int j = 1; j <= columnSize; ++j)
			gButtons[i][j].setPosition(j * CELL_SIZE + DISTANCE_BETWEEN, i * CELL_SIZE + DISTANCE_BETWEEN);
}

void createTableWithMine()
{
	// Tạo sự ngẫu nhiên cho game qua mỗi lần chơi
	srand(time(0));
	int mine = 0;
	while (mine < numOfMine)
	{
		int i = (rand() % rowSize) + 1;
		int j = (rand() % columnSize) + 1;
		if (board[i][j] == MINE)
			continue;
		else
		{
			board[i][j] = MINE;
			mine++;
			if (board[i - 1][j] != MINE)
				board[i - 1][j]++;
			if (board[i][j - 1] != MINE)
				board[i][j - 1]++;
			if (board[i + 1][j] != MINE)
				board[i + 1][j]++;
			if (board[i][j + 1] != MINE)
				board[i][j + 1]++;
			if (board[i - 1][j - 1] != MINE)
				board[i - 1][j - 1]++;
			if (board[i - 1][j + 1] != MINE)
				board[i - 1][j + 1]++;
			if (board[i + 1][j - 1] != MINE)
				board[i + 1][j - 1]++;
			if (board[i + 1][j + 1] != MINE)
				board[i + 1][j + 1]++;
		}
	}
}

bool checkWinning()
{
	bool win = false;
	for (int i = 1; i <= rowSize; ++i)
		for (int j = 1; j <= columnSize; ++j)
			if (board[i][j] == MINE)
				if (sBoard[i][j] == FLAG)
					win = true;
				else
					return false;
	return win;
}

void mineManager()
{
	// Tạo bảng đếm số mìn còn lại
	if (!gameOver && !isWinning)
	{
		SDL_Color textColor = {140, 140, 140, 255};
		mineLeft.str(std::string());
		mineLeft.clear();
		mineLeft << "Mine left: " << countMineLeft;
		if (!gMineLeftTexture.loadFromRenderedText(mineLeft.str().c_str(), textColor))
			std::cout << "Khong the tao bang dem so min con lai" << std::endl;

		gMineLeftTexture.render((screenWidth - gMineLeftTexture.getWidth()) / 2, 30);
	}
}

void flagManager()
{
	if (isWinning)
	{
		// In ra vị trí mìn
		for (int i = 1; i <= rowSize; ++i)
			for (int j = 1; j <= columnSize; ++j)
				if (sBoard[i][j] != FLAG)
					sBoard[i][j] = board[i][j];
		for (int i = 1; i <= rowSize; ++i)
			for (int j = 1; j <= columnSize; ++j)
				gButtons[i][j].render(i, j);

		// Tạo màn hình thắng
		gWin.render((screenWidth - gWin.getWidth()) / 2, 30);

		gPlayAgainTexture.render((screenWidth - gPlayAgainTexture.getWidth()) / 2, screenHeight - gPlayAgainTexture.getHeight());
	}
	if (gameOver)
	{
		// In ra vị trí mìn
		for (int i = 1; i <= rowSize; ++i)
			for (int j = 1; j <= columnSize; ++j)
				if (board[i][j] == MINE)
					sBoard[i][j] = board[i][j];
		for (int i = 1; i <= rowSize; ++i)
			for (int j = 1; j <= columnSize; ++j)
				gButtons[i][j].render(i, j);

		// Tạo màn hình thua
		gGameOver.render((screenWidth - gGameOver.getWidth()) / 2, 30);

		gPlayAgainTexture.render((screenWidth - gPlayAgainTexture.getWidth()) / 2, screenHeight - gPlayAgainTexture.getHeight());
	}
}

void playAgain(bool &quitGame)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		// Nếu người dùng nhấn 's' để chơi lại
		if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
			quitGame = true;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
		{
			countMineLeft = numOfMine;
			gameOver = false;
			isWinning = false;
			quitGame = false;

			// Tạo lại sân mìn
			for (int i = 0; i < rowSize + 2; ++i)
				fill(board[i].begin(), board[i].end(), 0);
			for (int i = 1; i <= rowSize; ++i)
				for (int j = 0; j <= columnSize; ++j)
					sBoard[i][j] = COVER;
			createTableWithMine();
		}
	}
}

void close()
{
	// Đóng các texture
	buttonSpriteSheetTexture.free();
	gMineLeftTexture.free();
	gWin.free();
	gGameOver.free();

	// Đóng font
	TTF_CloseFont(fGame);

	// Đóng cửa sổ và renderer
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;

	// Thoát SDL
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Variables.hpp"
#include "Texture.hpp"
#include "Button.hpp"

std::vector<std::vector<Button>> gButtons(rowSize + 2, std::vector<Button>(columnSize + 2));
bool init();
bool loadMedia();
void createTableWithMine();
bool checkWinning();
void mineManager();
void flagManager();
void playAgain(bool &quitGame);
void close();
int main(int argc, char *argv[])
{
	if (!init())
		std::cout << "Khoi tao chuong trinh that bai..." << std::endl;
	else if (!loadMedia())
		std::cout << "Khoi tao phong chu that bai..." << std::endl;
	else
	{
		bool quit = false;
		SDL_Event event;

		// Tao san choi moi
		createTableWithMine();

		// Vong lap xu li thao tac nguoi dung
		while (!quit)
		{
			while (!gameOver && !quit && !isWinning)
			{
				// Xu li cac thao tac
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;

					for (int i = 1; i <= rowSize; i++)
						for (int j = 1; j <= columnSize; j++)
							gButtons[i][j].handleEvents(&event);
					isWinning = checkWinning();
				}

				// Tao background
				SDL_SetRenderDrawColor(renderer, 204, 204, 204, 255);
				SDL_RenderClear(renderer);

				// Ve ban min
				for (int i = 1; i <= rowSize; i++)
					for (int j = 1; j <= columnSize; j++)
						gButtons[i][j].render(i, j);

				mineManager();

				flagManager();

				SDL_RenderPresent(renderer);
			}
			playAgain(quit);
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

		gWindow = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Khong the tao cua so game! SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
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

bool loadMedia()
{
	bool success = true;
	// Tao cac font chu se viet cho game
	fGameOver = TTF_OpenFont("E:\\Code\\Minesweeper-SDL-CMake\\src\\Font\\visitor1.ttf", 40);
	if (fGameOver == NULL)
	{
		std::cout << "Khong the mo font visitor1! SDL_ttf error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else
	{
		SDL_Color textColor = {140, 140, 140};
		if (!gGameOver.loadFromRenderedText("GAME OVER", textColor))
		{
			std::cout << "Khong the tao text!" << std::endl;
			success = false;
		}
	}

	fWin = TTF_OpenFont("E:\\Code\\Minesweeper-SDL-CMake\\src\\Font\\visitor1.ttf", 40);
	if (fWin == NULL)
	{
		std::cout << "Khong the mo font visitor1! SDL_ttf error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else
	{
		SDL_Color textColor = {140, 140, 140};
		if (!gWin.loadFromRenderedText("You Win", textColor))
		{
			std::cout << "Khong the tao text!" << std::endl;
			success = false;
		}
	}

	fPlayAgain = TTF_OpenFont("E:\\Code\\Minesweeper-SDL-CMake\\src\\Font\\visitor1.ttf", 40);
	if (fPlayAgain == NULL)
	{
		std::cout << "Khong the mo font visitor1! SDL_ttf error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else
	{
		SDL_Color textColor = {30, 100, 100};
		if (!gPlayAgainTexture.loadFromRenderedText("Press s to play again!", textColor))
		{
			std::cout << "Khong the tao text!" << std::endl;
			success = false;
		}
	}

	// Tao san min
	if (!gButtonSpriteSheetTexture.loadFromFile("E:\\Code\\Minesweeper-SDL-CMake\\src\\Images\\Tiles.png"))
	{
		std::cout << "Khong the load cac o min" << std::endl;
		success = false;
	}
	else
	{
		// Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
		{
			gSpriteClips[i].x = i * 32;
			gSpriteClips[i].y = 0;
			gSpriteClips[i].w = TILE_SIZE;
			gSpriteClips[i].h = TILE_SIZE;
		}
		// Tao vi tri cac o
		for (int i = 1; i <= rowSize; i++)
			for (int j = 1; j <= columnSize; j++)
				gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
	}
	return success;
}

void createTableWithMine()
{
	// Cau lenh tao su ngau nhien cho tro choi
	srand(time(0));
	int mine = 0;
	while (mine < numOfMine)
	{
		int i = rand() % rowSize + 1;
		int j = rand() % columnSize + 1;
		if (board[i][j] == MINE)
			continue;
		else
		{
			board[i][j] = MINE;
			mine++;
			if (board[i - 1][j] != MINE && i > 0)
				board[i - 1][j]++;
			if (board[i][j - 1] != MINE && j > 0)
				board[i][j - 1]++;
			if (board[i + 1][j] != MINE && i < rowSize - 1)
				board[i + 1][j]++;
			if (board[i][j + 1] != MINE && j < columnSize - 1)
				board[i][j + 1]++;
			if (board[i - 1][j - 1] != MINE && i > 0 && j > 0)
				board[i - 1][j - 1]++;
			if (board[i - 1][j + 1] != MINE && i > 0 && j < columnSize - 1)
				board[i - 1][j + 1]++;
			if (board[i + 1][j - 1] != MINE && j > 0 && i < rowSize - 1)
				board[i + 1][j - 1]++;
			if (board[i + 1][j + 1] != MINE && i < rowSize - 1 && j < columnSize - 1)
				board[i + 1][j + 1]++;
		}
	}
}

bool checkWinning()
{
	bool win = false;
	if (countTileLeft == numOfMine)
		win = true;
	return win;
}

void mineManager()
{
	// Tao bang dem so min con lai
	if (!gameOver && !isWinning)
	{
		SDL_Color textColor = {140, 140, 140, 255};
		mineLeft.str("");
		mineLeft << "Mine left: " << countMineLeft;
		if (!gMineLeftTexture.loadFromRenderedText(mineLeft.str().c_str(), textColor))
			std::cout << "Khong the tao bang dem so min con lai" << std::endl;

		gMineLeftTexture.render((screenWidth - gMineLeftTexture.getWidth()) / 2, 30);
	}
}

void flagManager()
{
	if (isWinning && !gameOver)
	{

		// Tao man hinh thang
		gWinningTexture.render(0, 0);

		// Tao text choi lai
		gPlayAgainTexture.render((screenWidth - gPlayAgainTexture.getWidth()) / 2, screenHeight - gPlayAgainTexture.getHeight());
	}
	if (gameOver)
	{
		// In ra vi tri min
		for (int i = 1; i <= rowSize; i++)
			for (int j = 1; j <= columnSize; j++)
				sBoard[i][j] = board[i][j];

		// Cap nhat man hinh
		gGameOver.render((screenWidth - gGameOver.getWidth()) / 2, 30);

		// Tao text choi lai
		gPlayAgainTexture.render((screenWidth - gPlayAgainTexture.getWidth()) / 2, screenHeight - gPlayAgainTexture.getHeight());
	}
}
//FIXME: Sua lai phan choi lai hoan chinh
void playAgain(bool &quitGame)
{
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests play again
		if (e.key.keysym.sym == SDLK_s)
		{
			//Recreate constants
			countMineLeft = numOfMine;
			countTileLeft = rowSize * columnSize;

			//Recreate flag
			gameOver = false;
			isWinning = false;
			quitGame = false;
		}
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			quitGame = true;
	}
}

void close()
{
	//Dong cac hinh anh
	gButtonSpriteSheetTexture.free();
	gMineLeftTexture.free();
	gWinningTexture.free();
	gGameOver.free();

	//Dong font
	TTF_CloseFont(fGameOver);
	TTF_CloseFont(fPlayAgain);
	TTF_CloseFont(fWin);
	fGameOver = NULL;
	fPlayAgain = NULL;
	fWin = NULL;

	//Dong cua so
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(renderer);
	gWindow = NULL;
	renderer = NULL;

	//Thoat SDL
	IMG_Quit();
	SDL_Quit();
}

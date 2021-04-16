#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Variables.hpp"
#include "Texture.hpp"
#include "Logic.hpp"
#include "StartScreen.hpp"
#include "Clock.hpp"

bool init();
std::string getSourcesPath();
bool loadMedia();
void resizeBoard(int rowSize, int columnSize);
void createTableWithMine();
bool checkWinning();
void mineManager();
void flagManager();
void playAgain(bool &quitGame, bool &quit);
void close();
int main(int argc, char *argv[])
{
	if (!init())
		std::cout << "Khoi tao chuong trinh that bai..." << std::endl;
	else if (!loadMedia())
		std::cout << "Khoi tao phong chu that bai..." << std::endl;
	else
	{
		bool quit = false, quitGame = false;
		while (!quit)
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
					quitGame = false;
					numOfMine = 10;
					rowSize = 9;
					columnSize = 9;
					resizeBoard(rowSize, columnSize);
					break;
				}
				case Medium:
				{
					screenWidth = 800;
					screenHeight = 800;
					quitGame = false;
					numOfMine = 40;
					rowSize = 16;
					columnSize = 16;
					resizeBoard(rowSize, columnSize);
					break;
				}
				case Quit:
				{
					quitGame = true;
					quit = true;
					break;
				}
				default:
					quitGame = true;
					break;
				}
				SDL_Event event;
				createTableWithMine();
				// Vòng lặp của game
				while (!quitGame)
				{
					Clock timer;
					while (!gameOver && !quitGame && !isWinning)
					{
						SDL_RenderClear(renderer);

						// Xử lí các thao tác người dùng
						while (SDL_PollEvent(&event) != 0)
						{
							if (event.type == SDL_QUIT)
							{
								quitGame = true;
								quit = true;
							}
							else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
							{
								quitGame = true;
								for (int i = 0; i < rowSize + 2; ++i)
									fill(board[i].begin(), board[i].end(), BLANK);
								for (int i = 0; i < rowSize + 2; ++i)
									fill(sBoard[i].begin(), sBoard[i].end(), COVER);
							}
							for (int i = 1; i <= rowSize; ++i)
								for (int j = 1; j <= columnSize; ++j)
									gButtons[i][j].handleEvents(&event);
							isWinning = checkWinning();
						}

						// Vẽ sân mìn
						for (int i = 1; i <= rowSize; ++i)
							for (int j = 1; j <= columnSize; ++j)
								gButtons[i][j].render(i, j);

						timer.showTime();

						mineManager();

						flagManager();

						SDL_RenderPresent(renderer);
					}
					playAgain(quitGame, quit);
				}
				break;
			}
			case Exit:
				quit = true;
				break;
			}
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
		window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Khong the tao cua so game! SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
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
				if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					std::cout << "Khong the khoi dong SDL_mixer! SDl_mixer error: " << Mix_GetError() << std::endl;
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

	std::string iconImgPath = resPath + std::string("Images/Icon.png");
	std::string mineImgPath = resPath + std::string("Images/Cells.png");
	std::string sound_onImgPath = resPath + std::string("Images/Sound.png");
	std::string sound_offImgPath = resPath + std::string("Images/Mute.png");

	std::string menuSoundPath = resPath + std::string("Sound/Menu.wav");
	std::string clickSoundPath = resPath + std::string("Sound/OpenCell.wav");
	std::string flagSoundPath = resPath + std::string("Sound/Flag.wav");
	std::string un_flagSoundPath = resPath + std::string("Sound/Unflag.wav");
	std::string mineSoundPath = resPath + std::string("Sound/MineHit.wav");
	std::string winSoundPath = resPath + std::string("Sound/Winning.wav");
	// Tạo màu background
	SDL_SetRenderDrawColor(renderer, 204, 204, 204, 255);

	// Tạo các font chữ sẽ hiện lên màn hình
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
	if (fGame == NULL)
	{
		std::cout << "Khong the mo font visitor1! SDL_ttf error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else if (!gGameOver.loadFromRenderedText("GAME OVER", {140, 140, 140}) || !gPlayAgainTexture.loadFromRenderedText("Press s to play again!", {30, 100, 100}) || !gWin.loadFromRenderedText("You Win", {140, 140, 140}))
	{
		std::cout << "Khong the tao text!" << std::endl;
		success = false;
	}

	// Load các âm thanh
	menuClick = Mix_LoadWAV(menuSoundPath.c_str());
	openCell = Mix_LoadWAV(clickSoundPath.c_str());
	flag = Mix_LoadWAV(flagSoundPath.c_str());
	unFlag = Mix_LoadWAV(un_flagSoundPath.c_str());
	mineFounded = Mix_LoadWAV(mineSoundPath.c_str());
	winning = Mix_LoadMUS(winSoundPath.c_str());
	if (menuClick == nullptr || openCell == nullptr || mineFounded == nullptr || winning == nullptr || flag == nullptr || unFlag == nullptr)
	{
		std::cout << "Khong the load am thanh!" << std::endl;
		success = false;
	}

	// Cắt các ô mìn từ hình ảnh Cells.png
	if (!buttonSpriteSheetTexture.loadFromFile(mineImgPath.c_str()))
	{
		std::cout << "Khong the load cac o min" << std::endl;
		success = false;
	}
	else
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			spriteClips[i].x = i * CELL_SIZE;
			spriteClips[i].y = 0;
			spriteClips[i].w = CELL_SIZE;
			spriteClips[i].h = CELL_SIZE;
		}
	if (!gameSound.loadFromFile(sound_onImgPath.c_str()))
	{
		std::cout << "Khong the load hinh anh cua am thanh" << std::endl;
		success = false;
	}

	// Tạo icon cho window
	SDL_Surface *icon = IMG_Load(iconImgPath.c_str());
	SDL_SetWindowIcon(window, icon);
	return success;
}

void resizeBoard(int rowSize, int columnSize)
{
	board.resize(rowSize + 2, std::vector<int>());
	for (int i = 0; i < rowSize + 2; ++i)
		board[i].resize(columnSize + 2, BLANK);
	sBoard.resize(rowSize + 2, std::vector<int>());
	for (int i = 0; i < rowSize + 2; ++i)
		sBoard[i].resize(columnSize + 2, COVER);
	gButtons.resize(rowSize + 2, std::vector<Button>());
	for (int i = 0; i < rowSize + 2; ++i)
		gButtons[i].resize(columnSize + 2);
	countMineLeft = numOfMine;
	DISTANCE_BETWEEN = (screenWidth - (rowSize + 2) * CELL_SIZE) / 2;
	SDL_SetWindowSize(window, screenWidth, screenHeight);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

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

		Mix_PlayMusic(winning, 0);
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

		Mix_PlayChannel(-1, mineFounded, 0);
	}
}

void playAgain(bool &quitGame, bool &quit)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			quitGame = true;
			quit = true;
			break;
		}
		case SDL_KEYDOWN:
		{
			// Nếu người dùng nhấn 's' để chơi lại
			if (event.key.keysym.sym == SDLK_s)
			{
				Mix_HaltMusic();
				countMineLeft = numOfMine;
				gameOver = false;
				isWinning = false;

				// Tạo lại sân mìn
				for (int i = 0; i < rowSize + 2; ++i)
					fill(board[i].begin(), board[i].end(), BLANK);
				for (int i = 1; i < rowSize + 2; ++i)
					fill(sBoard[i].begin(), sBoard[i].end(), COVER);
				createTableWithMine();
			}
			// Nhấn nút escape để quay về menu
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				Mix_HaltMusic();
				quitGame = true;
				gameOver = false;
				isWinning = false;
				for (int i = 0; i < rowSize + 2; ++i)
					fill(board[i].begin(), board[i].end(), BLANK);
				for (int i = 1; i < rowSize + 2; ++i)
					fill(sBoard[i].begin(), sBoard[i].end(), COVER);
			}
		}
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
	gPlayAgainTexture.free();
	gameSound.free();

	// Đóng font
	TTF_CloseFont(fGame);

	// Đóng các âm thanh
	Mix_FreeChunk(menuClick);
	Mix_FreeChunk(openCell);
	Mix_FreeChunk(mineFounded);

	// Đóng cửa sổ và renderer
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;

	// Thoát SDL
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
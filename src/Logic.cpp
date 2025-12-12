#include "Logic.hpp"
#include "Variables.hpp"
#include <cstdlib>

// Helper function to relocate mine on first click
void relocateMine(int clickI, int clickJ)
{
	// Remove mine from clicked position
	board[clickI][clickJ] = BLANK;

	// Decrease adjacent counts around the old mine position
	for (int di = -1; di <= 1; ++di)
		for (int dj = -1; dj <= 1; ++dj)
			if (board[clickI + di][clickJ + dj] != MINE && board[clickI + di][clickJ + dj] > 0)
				board[clickI + di][clickJ + dj]--;

	// Find a new position for the mine
	while (true)
	{
		int newI = (rand() % rowSize) + 1;
		int newJ = (rand() % columnSize) + 1;

		// Don't place mine on clicked cell or existing mines
		if ((newI == clickI && newJ == clickJ) || board[newI][newJ] == MINE)
			continue;

		// Place the mine in new position
		board[newI][newJ] = MINE;

		// Increase adjacent counts around new mine position
		for (int di = -1; di <= 1; ++di)
			for (int dj = -1; dj <= 1; ++dj)
				if (board[newI + di][newJ + dj] != MINE)
					board[newI + di][newJ + dj]++;

		break;
	}

	// Recalculate the clicked cell's adjacent mine count
	int count = 0;
	for (int di = -1; di <= 1; ++di)
		for (int dj = -1; dj <= 1; ++dj)
			if (board[clickI + di][clickJ + dj] == MINE)
				count++;
	board[clickI][clickJ] = count;
}

void Button::reveal(int i, int j)
{
	if (sBoard[i][j] == COVER || sBoard[i][j] == FLAG || sBoard[i][j] == QUESTION)
	{
		if (sBoard[i][j] == FLAG)
			countMineLeft++;
		sBoard[i][j] = board[i][j];
		if (board[i][j] == MINE)
			gameOver = true;
		if (sBoard[i][j] == BLANK)
		{
			if (i < rowSize && board[i + 1][j] != MINE)
				reveal(i + 1, j);
			if (i > 1 && board[i - 1][j] != MINE)
				reveal(i - 1, j);
			if (j < columnSize && board[i][j + 1] != MINE)
				reveal(i, j + 1);
			if (j > 1 && board[i][j - 1] != MINE)
				reveal(i, j - 1);
			if (i > 1 && j > 1 && board[i - 1][j - 1] != MINE)
				reveal(i - 1, j - 1);
			if (i < rowSize && j < columnSize && board[i + 1][j + 1] != MINE)
				reveal(i + 1, j + 1);
			if (i > 1 && j < columnSize && board[i - 1][j + 1] != MINE)
				reveal(i - 1, j + 1);
			if (i < rowSize && j > 1 && board[i + 1][j - 1] != MINE)
				reveal(i + 1, j - 1);
		}
	}
}

bool Button::correctFlag(int i, int j)
{
	int flags = 0;
	for (int k = i - 1; k <= i + 1; ++k)
		for (int l = j - 1; l <= j + 1; ++l)
			if (sBoard[k][l] == FLAG)
				flags++;
	if (flags == board[i][j])
		return true;
	else
		return false;
}

void Button::revealSurrounding(int i, int j)
{
	for (int k = i - 1; k <= i + 1; ++k)
		for (int l = j - 1; l <= j + 1; ++l)
			if (sBoard[k][l] != FLAG && sBoard[k][l] != QUESTION)
				reveal(k, l);
}

void Button::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::handleEvents(SDL_Event *event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		// Lấy vị trí con trỏ
		int x, y;
		SDL_GetMouseState(&x, &y);

		int i = (y - DISTANCE_BETWEEN) / CELL_SIZE;
		int j = (x - DISTANCE_BETWEEN) / CELL_SIZE;

		// Kiểm tra xem con trỏ có nhấn vào ô không
		bool inside = true;

		if (x < mPosition.x)
			inside = false;
		else if (x > mPosition.x + CELL_SIZE)
			inside = false;
		else if (y < mPosition.y)
			inside = false;
		else if (y > mPosition.y + CELL_SIZE)
			inside = false;
		if (inside)
			switch (event->button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				if (sBoard[i][j] == COVER)
				{
					// First click protection: relocate mine if clicked on one
					if (isFirstClick)
					{
						isFirstClick = false;
						if (board[i][j] == MINE)
							relocateMine(i, j);
					}
					reveal(i, j);
					if (board[i][j] != MINE && !isMute)
						Mix_PlayChannel(-1, openCell, 0);
				}
				break;
			}
			case SDL_BUTTON_RIGHT:
			{
				if (sBoard[i][j] == COVER)
				{
					if (countMineLeft == 0)
						break;
					if (!isMute)
						Mix_PlayChannel(-1, flag, 0);
					sBoard[i][j] = FLAG;
					countMineLeft--;
				}
				else if (sBoard[i][j] == FLAG)
				{
					if (!isMute)
						Mix_PlayChannel(-1, unFlag, 0);
					sBoard[i][j] = QUESTION;
					countMineLeft++;
				}
				else if (sBoard[i][j] == QUESTION)
				{
					sBoard[i][j] = COVER;
				}
				break;
			}
			case SDL_BUTTON_MIDDLE:
			{
				if (sBoard[i][j] < MINE && correctFlag(i, j))
				{
					revealSurrounding(i, j);
					if (!isMute)
						Mix_PlayChannel(-1, openCell, 0);
				}
				break;
			}
			}
	}
}

void Button::render(int i, int j)
{
	buttonSpriteSheetTexture.render(mPosition.x, mPosition.y, &spriteClips[sBoard[i][j]]);
}

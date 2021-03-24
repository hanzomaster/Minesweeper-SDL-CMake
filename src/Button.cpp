#include "Button.hpp"
#include "Variables.hpp"
void Button::reveal(int i, int j)
{
	if (sBoard[i][j] == COVER || sBoard[i][j] == FLAG)
	{
		if (sBoard[i][j] == FLAG)
			countMineLeft++;
		sBoard[i][j] = board[i][j];
		if (board[i][j] == MINE)
			gameOver = true;
		if (sBoard[i][j] == 0)
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
			if (sBoard[k][l] != FLAG)
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
					reveal(i, j);
					if (board[i][j] != MINE)
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
					Mix_PlayChannel(-1, flag, 0);
					sBoard[i][j] = FLAG;
					countMineLeft--;
				}
				else if (sBoard[i][j] == FLAG)
				{
					Mix_PlayChannel(-1, unFlag, 0);
					sBoard[i][j] = COVER;
					countMineLeft++;
				}
				break;
			}
			case SDL_BUTTON_MIDDLE:
			{
				if (sBoard[i][j] < MINE && correctFlag(i, j))
				{
					revealSurrounding(i, j);
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
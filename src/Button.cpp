#include "Button.hpp"

void Button::reveal(int i, int j)
{
	if (sBoard[i][j] == COVER || sBoard[i][j] == FLAG)
	{
		if (sBoard[i][j] == FLAG)
			countMineLeft++;
		sBoard[i][j] = board[i][j];
		countTileLeft--;
		if (sBoard[i][j] == 0)
		{
			if (i < rowSize - 1 && board[i + 1][j] != MINE)
				reveal(i + 1, j);
			if (i > 0 && board[i - 1][j] != MINE)
				reveal(i - 1, j);
			if (j < columnSize - 1 && board[i][j + 1] != MINE)
				reveal(i, j + 1);
			if (j > 0 && board[i][j - 1] != MINE)
				reveal(i, j - 1);
			if (i > 0 && j > 0 && board[i - 1][j - 1] != MINE)
				reveal(i - 1, j - 1);
			if (i < rowSize - 1 && j < columnSize - 1 && board[i + 1][j + 1] != MINE)
				reveal(i + 1, j + 1);
			if (i > 0 && j < columnSize - 1 && board[i - 1][j + 1] != MINE)
				reveal(i - 1, j + 1);
			if (i < rowSize - 1 && j > 0 && board[i + 1][j - 1] != MINE)
				reveal(i + 1, j - 1);
		}
	}
}

bool Button::correctFlag(int i, int j)
{
	for (int k = i - 1; k <= i + 1; ++k)
		for (int l = j - 1; l <= j + 1; ++l)
			if (board[k][l] == MINE && sBoard[k][l] != FLAG)
				return false;
	return true;
}

void Button::revealSurrounding(int i, int j)
{
	for (int k = i - 1; k <= i + 1; ++k)
		for (int l = j - 1; l <= j + 1; ++l)
			if (sBoard[k][l] != FLAG)
				sBoard[k][l] = board[k][l];
}

void Button::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::handleEvents(SDL_Event *event)
{
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		// Lay vi tri con tro
		int x, y;
		SDL_GetMouseState(&x, &y);

		int i = (y - DISTANCE_BETWEEN) / TILE_SIZE;
		int j = (x - DISTANCE_BETWEEN) / TILE_SIZE;

		// Kiem tra xem co nhan vao o khong
		bool inside = true;

		if (x < mPosition.x)
			inside = false;
		else if (x > mPosition.x + TILE_SIZE)
			inside = false;
		else if (y < mPosition.y)
			inside = false;
		else if (y > mPosition.y + TILE_SIZE)
			inside = false;
		if (inside)
			if (event->type == SDL_MOUSEBUTTONDOWN)
				switch (event->button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					reveal(i, j);
					if (board[i][j] == MINE)
						gameOver = true;
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					if (sBoard[i][j] == COVER)
					{
						if (countMineLeft == 0)
							break;
						sBoard[i][j] = FLAG;
						countMineLeft--;
					}
					else if (sBoard[i][j] == FLAG)
					{
						sBoard[i][j] = COVER;
						countMineLeft++;
					}
				}
				case SDL_BUTTON_MIDDLE:
				{
					if (sBoard[i][j] < MINE && correctFlag(i, j))
						revealSurrounding(i, j);
					break;
				}
				}
	}
}

void Button::render(int i, int j)
{
	// Tao trang thai o
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[sBoard[i][j]]);
}

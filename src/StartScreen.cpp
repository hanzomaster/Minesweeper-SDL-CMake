#include "StartScreen.hpp"

// Kiểm tra xem có bấm vào ô menu không
bool checkFocusWithRect(const int &x, const int &y, const SDL_Rect &rect)
{
	if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
		return true;
	return false;
}

// Generic menu display function to reduce code duplication
int showGenericMenu(const std::vector<std::string> &labels, int escapeReturnValue, int quitReturnValue)
{
	const int numItems = labels.size();
	std::vector<Texture> textMenu(numItems);
	std::vector<bool> selected(numItems, false);
	int posx = 0, posy = 0;

	for (int i = 0; i < numItems; ++i)
		textMenu[i].loadFromRenderedText(labels[i].c_str(), COLOR_BLACK);

	SDL_Event event;
	while (true)
	{
		frameStart = SDL_GetTicks();
		SDL_RenderClear(renderer);
		for (int i = 0; i < numItems; ++i)
			textMenu[i].render((screenWidth - textMenu[i].getWidth()) / 2, (screenHeight - textMenu[i].getHeight()) * 1 / 3 + i * MENU_ITEM_SPACING);
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return quitReturnValue;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return escapeReturnValue;
				break;
			case SDL_MOUSEMOTION:
			{
				posx = event.motion.x;
				posy = event.motion.y;
				for (int i = 0; i < numItems; ++i)
					if (checkFocusWithRect(posx, posy, textMenu[i].getRect()))
					{
						if (!selected[i])
						{
							selected[i] = true;
							textMenu[i].loadFromRenderedText(labels[i].c_str(), COLOR_RED);
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = false;
							textMenu[i].loadFromRenderedText(labels[i].c_str(), COLOR_BLACK);
						}
					}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				posx = event.button.x;
				posy = event.button.y;
				for (int i = 0; i < numItems; ++i)
					if (checkFocusWithRect(posx, posy, textMenu[i].getRect()))
					{
						for (int j = 0; j < numItems; ++j)
							textMenu[j].free();
						if (!isMute)
							Mix_PlayChannel(-1, menuClick, 0);
						return i;
					}
			}
			}
		}
		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

int showMenu()
{
	screenWidth = MENU_SCREEN_WIDTH;
	screenHeight = MENU_SCREEN_HEIGHT;
	SDL_SetWindowSize(window, screenWidth, screenHeight);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	std::vector<std::string> labels = {"New Game", "Exit"};
	return showGenericMenu(labels, Exit, Exit);
}

int showGameMode()
{
	std::vector<std::string> labels = {
		"Easy (9x9 10 mines)",
		"Medium (16x16 40 mines)",
		"Hard (30x16 99 mines)"
	};
	return showGenericMenu(labels, Back, Quit);
}

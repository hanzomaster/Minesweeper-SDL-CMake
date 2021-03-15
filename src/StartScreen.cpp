#include "StartScreen.hpp"

// Kiểm tra xem có bấm vào ô menu không
bool checkFocusWithRect(const int &x, const int &y, const SDL_Rect &rect)
{
	if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
		return true;
	return false;
}

int showMenu()
{
	static const int menuItem = 2;
	Texture textMenu[menuItem];
	bool selected[menuItem] = {false, false};
	const char *labels[menuItem] = {"New Game",
									"Exit"};
	int posx = 0, posy = 0;

	for (int i = 0; i < menuItem; ++i)
		textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});

	SDL_Event event;
	while (true)
	{
		SDL_RenderClear(renderer);
		for (int i = 0; i < menuItem; ++i)
			textMenu[i].render((screenWidth - textMenu[i].getWidth()) / 2, (screenHeight - textMenu[i].getHeight()) * 1 / 3 + i * 60);
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return -1;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			case SDL_MOUSEMOTION:
			{
				posx = event.motion.x;
				posy = event.motion.y;
				for (int i = 0; i < menuItem; ++i)
					if (checkFocusWithRect(posx, posy, textMenu[i].getRect()))
					{
						if (selected[i] == false)
						{
							selected[i] = true;
							textMenu[i].loadFromRenderedText(labels[i], {255, 0, 0});
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = false;
							textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});
						}
					}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				posx = event.button.x;
				posy = event.button.y;
				for (int i = 0; i < menuItem; ++i)
					if (checkFocusWithRect(posx, posy, textMenu[i].getRect()))
						return i;
			}
			}
		}
		SDL_RenderPresent(renderer);
	}
}

int showGameMode()
{
	static const int numOfGameMode = 2;
	Texture textMenu[numOfGameMode];
	bool selected[numOfGameMode] = {false, false};
	const char *labels[numOfGameMode] = {"Easy (9x9 10 mines)",
										 "Medium (13x13 25 mines)"};
	int posx = 0, posy = 0;

	for (int i = 0; i < numOfGameMode; ++i)
		textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});

	SDL_Event event;
	while (true)
	{
		SDL_RenderClear(renderer);
		for (int i = 0; i < numOfGameMode; ++i)
			textMenu[i].render((screenWidth - textMenu[i].getWidth()) / 2, (screenHeight - textMenu[i].getHeight()) * 1 / 3 + i * 60);
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return -1;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			case SDL_MOUSEMOTION:
			{
				posx = event.motion.x;
				posy = event.motion.y;
				for (int i = 0; i < numOfGameMode; ++i)
					if (checkFocusWithRect(posx, posy, textMenu[i].getRect()))
					{
						if (selected[i] == false)
						{
							selected[i] = true;
							textMenu[i].loadFromRenderedText(labels[i], {255, 0, 0});
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = false;
							textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});
						}
					}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				posx = event.button.x;
				posy = event.button.y;
				for (int i = 0; i < numOfGameMode; ++i)
					if (checkFocusWithRect(posx, posy, textMenu[i].getRect()))
						return i;
			}
			}
		}
		SDL_RenderPresent(renderer);
	}
}
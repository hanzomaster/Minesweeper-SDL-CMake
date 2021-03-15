#pragma once
#include <SDL.h>
#include "Texture.hpp"
#include "Variables.hpp"

bool checkFocusWithRect(const int &x, const int &y, const SDL_Rect &rect);
int showMenu();
int showGameMode();
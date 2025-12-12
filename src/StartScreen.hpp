#pragma once
#include <SDL.h>
#include "Texture.hpp"
#include "Variables.hpp"
#include <vector>
#include <string>

bool checkFocusWithRect(const int &x, const int &y, const SDL_Rect &rect);

// Generic menu display function
int showGenericMenu(const std::vector<std::string> &labels, int escapeReturnValue, int quitReturnValue);

int showMenu();
int showGameMode();

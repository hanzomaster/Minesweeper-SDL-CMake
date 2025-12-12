#include "Clock.hpp"
#include <fstream>
#include <string>

// High scores: 0 means no score yet, -1 is used internally for "no best time"
int highScores[3] = {0, 0, 0};

Clock::Clock()
{
	start = SDL_GetTicks();
	timer = 0;
}

Clock::~Clock()
{
	gTime.free();
}

void Clock::showTime()
{
	current_time = SDL_GetTicks();
	if (current_time - start >= 1000)
	{
		timer++;
		start = current_time;
	}
	gTime.loadFromRenderedText(std::to_string(timer), {140, 140, 140});
	gTime.render(screenWidth - gTime.getWidth() - 20, 30);
}

std::string getHighScorePath()
{
	std::string baseRes;
	char *basePath = SDL_GetBasePath();
	if (basePath)
	{
		baseRes = basePath;
		SDL_free(basePath);
	}
	int pos = baseRes.find("build");
	baseRes = baseRes.substr(0, pos) + "highscores.txt";
	for (size_t i = 0; i < baseRes.length(); ++i)
		if (baseRes[i] == '\\')
			baseRes[i] = '/';
	return baseRes;
}

void loadHighScores()
{
	std::ifstream file(getHighScorePath());
	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			if (!(file >> highScores[i]))
				highScores[i] = 0;
		}
		file.close();
	}
}

void saveHighScores()
{
	std::ofstream file(getHighScorePath());
	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
			file << highScores[i] << std::endl;
		file.close();
	}
}

bool checkAndUpdateHighScore(int difficulty, int time)
{
	if (difficulty < 0 || difficulty > 2)
		return false;

	// If no previous score or new time is better (lower)
	if (highScores[difficulty] == 0 || time < highScores[difficulty])
	{
		highScores[difficulty] = time;
		saveHighScores();
		return true;
	}
	return false;
}

int getHighScore(int difficulty)
{
	if (difficulty < 0 || difficulty > 2)
		return 0;
	return highScores[difficulty];
}

#pragma once
#include "Variables.hpp"

class Clock
{
private:
	Texture gTime;
	int timer;
	Uint32 start, current_time;

public:
	Clock();
	~Clock();
	void showTime();
	int getTime() const { return timer; }
};

// High score functions
void loadHighScores();
void saveHighScores();
bool checkAndUpdateHighScore(int difficulty, int time);
int getHighScore(int difficulty);

// High score storage (indexed by difficulty: 0=Easy, 1=Medium, 2=Hard)
extern int highScores[3];

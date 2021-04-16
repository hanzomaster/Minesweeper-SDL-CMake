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
};

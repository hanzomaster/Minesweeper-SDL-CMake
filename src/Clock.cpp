#include "Clock.hpp"

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
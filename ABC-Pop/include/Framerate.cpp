

#include "Framerate.h"
#include <SDL.h>

Framerate Framerate::fpsControl;

Framerate::Framerate()
: oldTime(0),lastTime(0),speedFactor(0),numFrames(0),frames(0)
{
}

void Framerate::Update()
{
	if (oldTime + 1000 < SDL_GetTicks())
	{
		oldTime = SDL_GetTicks();
		numFrames = frames;
		frames = 0;
	}
	speedFactor = ((SDL_GetTicks() - lastTime) / 1000.0f) * 60.0f;
	lastTime = SDL_GetTicks();
	frames++;
}

int Framerate::GetFPS()
{
	return numFrames;
}

float Framerate::GetSpeedFactor()
{
	return speedFactor;
}

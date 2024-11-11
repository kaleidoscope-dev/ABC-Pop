
#ifndef FRAMERATE_H
#define FRAMERATE_H

class Framerate
{
public:
	Framerate();

	void Update();

	int GetFPS();
	float GetSpeedFactor();

	static Framerate fpsControl;

private:
	int oldTime;
	int lastTime;

	float speedFactor;

	int numFrames;
	int frames;
};

#endif

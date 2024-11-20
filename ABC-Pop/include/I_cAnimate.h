#pragma once


#include "gameapi.h"

class I_cAnimate {
private:
	int    CurrentFrame;

	int     FrameInc;

private:
	int     FrameRate; //Milliseconds

	long    OldTime;

public:
	int    MaxFrames;

	bool    Oscillate;

public:
	I_cAnimate();
	void Init(uint8_t max_frames, uint8_t rate);
	bool OnAnimate(void);

public:
	void SetFrameRate(int Rate);

	void SetCurrentFrame(int Frame);

	int GetCurrentFrame();
};
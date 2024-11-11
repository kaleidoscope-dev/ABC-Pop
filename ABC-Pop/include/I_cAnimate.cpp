#include "I_cAnimate.h"

I_cAnimate::I_cAnimate()
{
	CurrentFrame = 0;
	MaxFrames = 6;
	FrameInc = 1;

	FrameRate = 50; //Milliseconds
	OldTime = 0;

	Oscillate = false;
}


void I_cAnimate::Init(uint8_t max_frames, uint8_t rate)
{
	MaxFrames = max_frames;
	FrameRate = rate;
}




bool I_cAnimate::OnAnimate(void) 
{
	if (OldTime + FrameRate > SDL_GetTicks()) {
		return false;
	}

	OldTime = SDL_GetTicks();

	CurrentFrame += FrameInc;

	if (Oscillate) {
		if (FrameInc > 0) {
			if (CurrentFrame >= MaxFrames) {
				FrameInc = -FrameInc;
			}
		}
		else {
			if (CurrentFrame <= 0) {
				FrameInc = -FrameInc;
			}
		}
	}
	else {
		if (CurrentFrame >= MaxFrames) {
			CurrentFrame = 0;
		}
	}

 return true;
}

void I_cAnimate::SetFrameRate(int Rate) {
	FrameRate = Rate;
}

void I_cAnimate::SetCurrentFrame(int Frame) {
	if (Frame < 0 || Frame >= MaxFrames) return;

	CurrentFrame = Frame;
}

int I_cAnimate::GetCurrentFrame() 
{
	return CurrentFrame;
}
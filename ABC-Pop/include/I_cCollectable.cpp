#include "I_cCollectable.h"
#include "I_cAssetmanager.h"


int x, y;

I_cCollectable::I_cCollectable()
{
 rect_.x = GAMEAPI_WINDOW_W;
 posx = GAMEAPI_WINDOW_W;
 rect_.y = 200;
 x = y = 0;
}


I_cCollectable::~I_cCollectable()
{
}




void I_cCollectable::Draw(bool update)
{
 
 if (update)
    {
	 wavefunc();
     posx -=1.7;
	 rect_.x = (int)posx;
     //rect_.y = y + 200;
     rect_.y = y + GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H,40);
	}

 rect_.w = GAMEAPI_BALLOON_W;
 rect_.h = GAMEAPI_BALLOON_H;

 SDL_RenderCopy(gAssetManager->GetRenderer(), tex, NULL, &rect_);
}


bool I_cCollectable::IsClicked(int mx, int my)
{
	SDL_Point pt;
	pt.x = mx;
	pt.y = my;

	if (SDL_PointInRect(&pt, &rect_))
		return true;


	return false;
}



void I_cCollectable::wavefunc()
{
	static float angle = 0.0;
	float angle_stepsize = 0.02;
	//int length = 400;
	int length = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H,40);

	// calculate x, y from a vector with known length and angle
	x = length * cos(angle);
	y = length * sin(angle);

	//printf("%d, %d\n",x,y);

	angle += angle_stepsize;

	if (angle > 2 * GAMEAPI_PI)   // napravi puni krug
		angle = 0;

}
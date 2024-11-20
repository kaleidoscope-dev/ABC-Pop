#include "include/gameapi.h"
#include "I_cMarkerButton.h"


I_cMarkerButton::I_cMarkerButton()
{
 update_ = true;
}

I_cMarkerButton::~I_cMarkerButton()
{
}

void I_cMarkerButton::SetUpdate(bool b)
{
 update_ = b;
}


void I_cMarkerButton::Draw(void)
{
   if (update_)
      {
	   wavefunc();
       widget_rect_.y += y;
      }

	if (!visible_)
		return;

	RenderSkin();

	SDL_Rect rc = widget_rect_;

	for (size_t c=0;c<vPictureList.size();c++)
			{
			PICTURE *ptr_pic = &vPictureList[c];


            if (update_)
			   ptr_pic->rect.y += y;


			SDL_RenderCopy(AndUIn::renderer_, ptr_pic->tex, NULL, &ptr_pic->rect);
	}
	 


}



void I_cMarkerButton::wavefunc()
{
	static float angle = 0.0;
	float angle_stepsize = 0.09;
	int length = 3;

	// calculate x, y from a vector with known length and angle
	x = length * cos(angle);
	y = length * sin(angle);

	//printf("%d, %d\n",x,y);

	angle += angle_stepsize;

	if (angle > 2 * GAMEAPI_PI)  
		angle = 0;

}
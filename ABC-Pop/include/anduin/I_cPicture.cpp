#include "I_cPicture.h"



I_cPicture::I_cPicture()
{

	widget_rect_.x = 0;
	widget_rect_.y = 0;
	widget_rect_.w = AndUIn::ANDUIN_Window_W;
	widget_rect_.h = AndUIn::ANDUIN_Window_H;
    show_ = true;
    type_ = ANDUIN_CONTROL_PICTURE;
}


I_cPicture::~I_cPicture()
{
}


void I_cPicture::SetTexture(SDL_Texture *tex)
{
 tex_background = tex;
}



void I_cPicture::Draw(void)
{
 if (show_)
	SDL_RenderCopy(AndUIn::renderer_, tex_background, NULL, &widget_rect_);
}



void I_cPicture::SetPos(int x, int y, int w, int h)
{

	I_cWidget::SetPos(x,y,w,h);
}

void I_cPicture::SetShow(bool b)
{
 show_ = b;
}
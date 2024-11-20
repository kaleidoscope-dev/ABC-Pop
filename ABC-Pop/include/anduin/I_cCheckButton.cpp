#include "I_cCheckButton.h"
#include <string>


I_cCheckButton::I_cCheckButton(std::string nameid)
{
 type_ = ANDUIN_CONTROL_BUTTON;
 I_cWidget::nameId_ = "wdg_button";
 m_name_ = nameid;
 check_ = false;
}



I_cCheckButton::~I_cCheckButton()
{
}



void I_cCheckButton::SetCheckTexture(SDL_Texture * on, SDL_Texture * off)
{
	tex_on_ = on;
	tex_off_ = off;

}

void I_cCheckButton::Draw(void)
{
 if (check_)
    {
		 this->tex_current_ = tex_on_;
		}else this->tex_current_ = tex_off_;

 I_cButton::Draw();
}


void I_cCheckButton::SetCheck(bool ch)
{
 check_ = ch;
}





void I_cCheckButton::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{


	if (!visible_)
		return;

	if (!enabled_)
		return;

	if (type == AndUIn::EVENT_BUTTON_UP)
	   {
		  int x = 0, y = 0;
		  SDL_GetMouseState(&x, &y);
		  SDL_Point pt = { x,y };
		
		  if (SDL_PointInRect(&pt, &widget_rect_))
			   {
				  SetCheck(!check_);
	    	 }
	    }
	  

	I_cButton::HandleEvent(type);
}

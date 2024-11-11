#include "I_cButton.h"
#include <string>


I_cButton::I_cButton(std::string nameid)
{
 custom_tex_ = false;
 ptr_Data_ = NULL;
 visible_ = true;
 usingFonts_ = true;
 enabled_ = true;
 OnClick.bind(this, &I_cButton::dummy);
 type_ = ANDUIN_CONTROL_BUTTON;

 tex_text_ = NULL;
 tex_current_ = NULL;
 tex_background = NULL;
 tex_button_down_ = NULL;
 tex_button_up_ = NULL;

 ptr_Data_ = NULL;
 I_cWidget::nameId_ = "wdg_button";
 m_name = nameid;
 transparent_ = false;
}



I_cButton::~I_cButton()
{
 SDL_DestroyTexture(tex_text_);
 if (ptr_Data_)
     delete ptr_Data_;
}




void I_cButton::SetText(std::string txt, SDL_Color clr)
{
 txt_ = txt;
 txt_clr_ = clr;
 createTextTexture();


 int htx = (rect_text_.w / 2) - (AndUIn::font_size_ / 2);
 int hrx = widget_rect_.w / 2;

 rect_text_.x = widget_rect_.x + (hrx - htx) - AndUIn::font_size_ / 2;

}



void I_cButton::SetShowText(bool s)
{
 show_txt_ = s;
}






void I_cButton::Draw(void)
{

 if (!visible_)
 	 return;


 if (!transparent_)
    {
     RenderSkin();

     SDL_Rect rc = widget_rect_;

     if (usingFonts_)
        {

	     if (show_txt_)
	     {
          if (tex_text_) // hmm??
			 SDL_RenderCopy(AndUIn::renderer_, tex_text_, NULL, &rect_text_);
		 }

     }else  stringRGBA(AndUIn::renderer_, widget_rect_.x + widget_rect_.w / 2 - (int)txt_.length() * 4, widget_rect_.y + widget_rect_.h / 2, txt_.c_str(), txt_clr_.r, txt_clr_.g, txt_clr_.b, 255);
    }

	
	    

 I_cWidget::Draw();
}



bool I_cButton::IsPressed(void)
{
 if (tex_current_ == tex_button_down_)
	return true;

 return false;
}


void I_cButton::SetPressedState(bool press)
{
 if (press)
    {
	 tex_current_ = tex_button_down_;
	}else tex_current_ = tex_button_up_;
}

std::string I_cButton::GetText()
{
	return txt_;
}


void I_cButton::SetTexture(SDL_Texture *tex_up, SDL_Texture *tex_dwn)
{
 tex_button_up_ = tex_up;
 tex_button_down_ = tex_dwn;
 tex_current_ = tex_button_up_;
 custom_tex_ = true;
}



void I_cButton::RenderSkin(void)
{

	if (!custom_tex_)
    {
		 int x, y, x1, y1;
		 x = widget_rect_.x, y = widget_rect_.y;
		 x1 = widget_rect_.x + widget_rect_.w, y1 = widget_rect_.y + widget_rect_.h;

		 roundedBoxRGBA(AndUIn::renderer_, x+1, y, x1-1, y1, 2, 125, 125, 125, 255);  // prvi sloj (pozadina)
		 roundedBoxRGBA(AndUIn::renderer_, x+1, y, x1-1, y1-1, 2, 0, 0, 0, 255);
		 lineRGBA(AndUIn::renderer_, x+3 , y+2 , x1-3, y+2 , 125, 125, 125, 255);
		}



	//SDL_RenderCopy(AndUIn::renderer_, tex_current_, NULL, &tex_current_rect_);
	SDL_RenderCopy(AndUIn::renderer_, tex_current_, NULL, &widget_rect_);
}






void I_cButton::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{

 if (!visible_)
     return;

 if (!enabled_)
     return;

	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);  // NOTE: we really shouldn't call this here 
	SDL_Point pt = { x,y };


	switch (type)
	{
	case AndUIn::EVENT_BUTTON_DOWN:
		if (SDL_PointInRect(&pt, &widget_rect_))
			tex_current_ = tex_button_down_;

		break;

	case AndUIn::EVENT_BUTTON_UP:
		tex_current_ = tex_button_up_;
		if (SDL_PointInRect(&pt, &widget_rect_))
			OnClick(ptr_Data_);
	
		break;

	}

}



void I_cButton::SetPos(int x, int y, int w, int h)
{
	I_cWidget::SetPos(x,y,w,h);
	
	rect_text_.x = x;
	rect_text_.y = y + h/4;
	rect_text_.w = AndUIn::font_size_*2;
	rect_text_.h = h/2;

	if (!custom_tex_)
	   createUIBox();
}


void I_cButton::createUIBox(void)
{

	SDL_Surface *up_surface = SDL_CreateRGBSurface(0, widget_rect_.w, widget_rect_.h, 32, 0, 0, 0, 0);
	SDL_Surface *down_surface = SDL_CreateRGBSurface(0, widget_rect_.w, widget_rect_.h, 32, 0, 0, 0, 0);

	SDL_Color c1 = { 72,72,72,255 };
	SDL_Color c2 = { 60,60,60,255 };

	tex_button_up_ = vertgradient(up_surface, c1, c2);

	SDL_Color c3 = { 36,36,36,255 };
	SDL_Color c4 = { 29,29,29,255 };

	tex_button_down_ = vertgradient(down_surface, c3, c4);

	tex_current_ = tex_button_up_;

	SDL_FreeSurface(up_surface);
	SDL_FreeSurface(down_surface);

}

void I_cButton::dummy(void *)
{
}

void I_cButton::SetUserData(void *ptr_data)
{
 ptr_Data_ = ptr_data;
}

void *I_cButton::GetUserData(void)
{
 return ptr_Data_;
}



void I_cButton::SetVisible(bool visible)
{
 visible_ = visible;
}

void I_cButton::SetEnable(bool e)
{
 enabled_ = e;
}

void I_cButton::SetTransparent(bool b)
{
 transparent_ = b;
}

void I_cButton::SetUsingFonts(bool f)
{
	usingFonts_ = f;
}



void I_cButton::createTextTexture(void)
{

	SDL_Surface *surf_letter = TTF_RenderText_Blended(AndUIn::font_ol_, txt_.c_str(), AndUIn::White);
	rect_text_.w = (int)txt_.length() * 32;//AndUIn::font_size_;  // TODO: define lettersize


	tex_text_ = SDL_CreateTextureFromSurface(AndUIn::renderer_, surf_letter); //now you can convert it into a texture

	SDL_FreeSurface(surf_letter);


}


SDL_Texture *I_cButton::GetTexture(void)
{
 return tex_current_;
}

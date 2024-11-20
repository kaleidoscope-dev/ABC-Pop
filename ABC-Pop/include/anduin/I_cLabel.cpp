#include "I_cLabel.h"



I_cLabel::I_cLabel()
{
 custom_tex_ = false;
 render_bck_ = true;
}


I_cLabel::~I_cLabel()
{
}




void I_cLabel::SetText(std::string txt)
{
 txt_ = txt;
 createTextTexture();


}


void I_cLabel::SetText(const char *format, ...)
{
	char out[256];
	va_list arglist;

	va_start(arglist, format);
#ifdef __ANDROID__
	vsprintf(out, format, arglist);
#else
	vsprintf_s(out, format, arglist);
#endif
	va_end(arglist);
	
	std::string s = out;

	txt_ = s;
	createTextTexture();
}




std::string I_cLabel::GetText(void)
{
	return txt_;
}

void I_cLabel::Draw(void)
{
 if (render_bck_)
	   RenderSkin();


  if (AndUIn::font_)   
     {
	  SDL_Rect rc = widget_rect_;
	  rc.x += 5;
	  rc.y += 7;
	  rc.w -= 7;
	  rc.h -= 8;
	  SDL_RenderCopy(AndUIn::renderer_, tex_text_, NULL, &rc);
	 }else stringRGBA(AndUIn::renderer_, widget_rect_.x + widget_rect_.w / 2 - (int)txt_.length() * 4, widget_rect_.y + widget_rect_.h / 2, txt_.c_str(), 0, 255, 0, 255);


}



void I_cLabel::RenderSkin(void)
{
 if (!custom_tex_)
    {
		 int x, y, x1, y1;
		 x = widget_rect_.x, y = widget_rect_.y;
		 x1 = widget_rect_.x + widget_rect_.w, y1 = widget_rect_.y + widget_rect_.h;


	   roundedBoxRGBA(AndUIn::renderer_, x, y, x1, y1 + 2, 2, 125, 125, 125, 255);
	   roundedBoxRGBA(AndUIn::renderer_, x, y, x1, y1, 1, 0, 0, 0, 255);
	   thickLineRGBA(AndUIn::renderer_, x + 3, y + 4, x1 - 2, y + 4, 1, 125, 125, 125, 255);
		 SDL_RenderCopy(AndUIn::renderer_, tex_background, NULL, &widget_rect_);
    }
}


void I_cLabel::SetPos(int x, int y, int w, int h)
{
	I_cWidget::SetPos(x,y,w,h);
	

	createUIBox();
}

void I_cLabel::createUIBox(void)
{

	SDL_Surface *s = SDL_CreateRGBSurface(0, widget_rect_.w, widget_rect_.h, 32, 0, 0, 0, 0);

	SDL_Color c1 = { 72,72,72,255 };
	SDL_Color c2 = { 60,60,60,255 };



	tex_background = vertgradient(s,c1,c2);


	SDL_FreeSurface(s);

}




void I_cLabel::createTextTexture(void)
{

	SDL_Color white = { 0xFF, 0xFF, 0xFF };

	SDL_Surface *surf_letter = TTF_RenderText_Blended(AndUIn::font_ol_, txt_.c_str(), white);


	tex_text_ = SDL_CreateTextureFromSurface(AndUIn::renderer_, surf_letter); //now you can convert it into a texture

	SDL_FreeSurface(surf_letter);

}
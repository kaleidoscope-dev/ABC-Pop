#include "I_cTextBox.h"



I_cTextBox::I_cTextBox()
{
}


I_cTextBox::~I_cTextBox()
{
}



void I_cTextBox::SetText(const char *format, ...)
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
	CreateTextTexture(AndUIn::White);
}



void I_cTextBox::SetText(std::string txt, SDL_Color clr)
{
	txt_ = txt;
	createUIBox();
	CreateTextTexture(clr);
}

std::string I_cTextBox::GetText(void)
{
	return txt_;
}

void I_cTextBox::Draw(void)
{
	if (render_bck_)
		RenderSkin();

	if (AndUIn::font_)
	{
		// text se crta od sredine
		SDL_Rect rc = widget_rect_;

		int htx = (rect_text_.w/2) - (AndUIn::font_size_/2);
		int hrx = widget_rect_.w/2;

		rc.x = widget_rect_.x + (hrx-htx) - AndUIn::font_size_/2;
		rc.y = rect_text_.y;
		rc.w = rect_text_.w;
		rc.h = rect_text_.h;

		SDL_RenderCopy(AndUIn::renderer_, tex_text_, NULL, &rc);
	}
	else stringRGBA(AndUIn::renderer_, widget_rect_.x + widget_rect_.w / 2 - (int)txt_.length() * 4, widget_rect_.y + widget_rect_.h / 2, txt_.c_str(), 180, 180, 180, 255);

	I_cWidget::Draw();

}



void I_cTextBox::RenderSkin(void)
{
	int x, y, x1, y1;
	x = widget_rect_.x, y = widget_rect_.y;
	x1 = widget_rect_.x + widget_rect_.w, y1 = widget_rect_.y + widget_rect_.h;

	roundedBoxRGBA(AndUIn::renderer_, x + 1, y+1, x1 - 1, y1, 1, 125, 125, 125, 255);  // prvi sloj (pozadina - siva)
	roundedBoxRGBA(AndUIn::renderer_, x + 1, y+1, x1 - 1, y1 - 1, 1, 0, 0, 0, 255);  // drugi sloj, crna
	lineRGBA(AndUIn::renderer_, x + 3, y + 3, x1 - 3, y + 3, 125, 125, 125, 255);

	// TODO: nr se mora postaviti kao u button - tod je unutrasnjost boxa. mora biti malo manjo
	SDL_Rect nr = widget_rect_;
	nr.x += 3;
	nr.y += 5;
	nr.w -= 5;
	nr.h -= 6;
	SDL_RenderCopy(AndUIn::renderer_, tex_current_, NULL, &nr);

}


void I_cTextBox::HandleEvent(SDL_Event *event)
{
 I_cWidget::HandleEvent(event);
}



// Prebaciti u TextBoxInput
void I_cTextBox::AddLetter(char ch)
{

	// ako je velicina unesenog texta veca of kontrole, nemoj stvarati nova slova

    int txt_size = (int)txt_.length() + 1;
    int fs = (int)AndUIn::font_size_;
	if ((txt_size * fs) > widget_rect_.w)
		return;


	txt_ += ch;
	SDL_Color white = { 0xFF, 0xFF, 0xFF };

	SDL_Surface *surf_letter = TTF_RenderText_Blended(AndUIn::font_ol_, txt_.c_str(), white);
	rect_text_.w = (int)txt_.size() * AndUIn::font_size_;  // TODO: define velicina slova

	tex_text_ = SDL_CreateTextureFromSurface(AndUIn::renderer_, surf_letter); //now you can convert it into a texture

	SDL_FreeSurface(surf_letter);
	
}


void I_cTextBox::CreateTextTexture(SDL_Color clr)
{
	//if ((txt_.size() + 1) * AndUIn::font_size_ > rect_.w)
	//	return;



	SDL_Surface *surf_letter = TTF_RenderText_Blended(AndUIn::font_ol_, txt_.c_str(), clr);
	rect_text_.w = txt_.size() * AndUIn::font_size_;  // TODO: define velicina slova


	tex_text_ = SDL_CreateTextureFromSurface(AndUIn::renderer_, surf_letter); //now you can convert it into a texture

	SDL_FreeSurface(surf_letter);


}



void I_cTextBox::SetPos(int x, int y, int w, int h)
{
	I_cWidget::SetPos(x, y, w, h);


	rect_text_.x = x + 3;
	rect_text_.y = y + 5;
	rect_text_.w = 20;
	rect_text_.h = h - 6;
	createUIBox();
}





void I_cTextBox::createUIBox(void)
{
 if (AndUIn::using_textures_)
    {
	 tex_current_ = AndUIn::text_box_tex_;
	 return;
	}

	SDL_Surface *s = SDL_CreateRGBSurface(0, widget_rect_.w, widget_rect_.h, 32, 0, 0, 0, 0);

	SDL_Color c1 = { 72,72,72,255 };
	SDL_Color c2 = { 60,60,60,255 };

	tex_current_ = vertgradient(s, c1, c2);


	SDL_FreeSurface(s);

}

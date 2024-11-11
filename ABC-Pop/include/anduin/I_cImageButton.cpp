#include "I_cImageButton.h"
#include <string>

I_cImageButton::I_cImageButton(std::string nameid)
{
 type_ = ANDUIN_CONTROL_BUTTON;
 I_cWidget::nameId_ = "wdg_button";
 pic.tex = NULL;
}



I_cImageButton::~I_cImageButton()
{
	vPictureList.clear();
}


void I_cImageButton::SetImage(SDL_Texture *tex, AndUIn::Orientation orientation)
{
 int posx,posy,sizew,sizeh;
 image_ = tex;
 orient_ = orientation;

 switch(orientation)
       {
			  case AndUIn::OrientationLeft:
					posx = AndUIn::GetPercentage(2, widget_rect_.w);
					posy = AndUIn::GetPercentage(10, widget_rect_.h);
					sizew = AndUIn::GetPercentage(20, widget_rect_.w);
					sizeh = AndUIn::GetPercentage(75, widget_rect_.h);
					pic.rect = AndUIn::GetRect(widget_rect_.x + posx, widget_rect_.y + posy, sizew, sizeh);

					// ako se text preklapa sa image, smanji text
					if (pic.rect.x + pic.rect.w > rect_text_.x)
					   {
						  rect_text_.x = pic.rect.x + pic.rect.w;
							rect_text_.w -= pic.rect.w;
						 }

					break;

				case AndUIn::OrientationMiddle:
					posx = AndUIn::GetPercentage(50, widget_rect_.w);
					posy = AndUIn::GetPercentage(10, widget_rect_.h);
					sizew = AndUIn::GetPercentage(20, widget_rect_.w);
					sizeh = AndUIn::GetPercentage(75, widget_rect_.h);
					pic.rect = AndUIn::GetRect(widget_rect_.x + posx - sizew/2, widget_rect_.y + posy, sizew, sizeh);
					break;

			  // TODO: Isto kao i za left ali sa desne strane
				case AndUIn::OrientationRight:
					posx = AndUIn::GetPercentage(77, widget_rect_.w);
					posy = AndUIn::GetPercentage(10, widget_rect_.h);
					sizew = AndUIn::GetPercentage(20, widget_rect_.w);
					sizeh = AndUIn::GetPercentage(75, widget_rect_.h);
					pic.rect = AndUIn::GetRect(widget_rect_.x + posx, widget_rect_.y + posy, sizew, sizeh);
					break;

				default:
				break;

 }


 pic.tex = tex;

}


void I_cImageButton::Draw(void)
{
	I_cButton::Draw();

	if (visible_)
	   {
		if (pic.tex != NULL)
			SDL_RenderCopy(AndUIn::renderer_, pic.tex, NULL, &pic.rect);
	    
			if (show_pic_)
			{
				for (size_t c = 0; c < vPictureList.size(); c++)
				{
					PICTURE *ptr_pic = &vPictureList[c];
					SDL_RenderCopy(AndUIn::renderer_, ptr_pic->tex, NULL, &ptr_pic->rect);
				}
			}
	   }
	

}



void I_cImageButton::SetShowPic(bool s)
{
	show_pic_ = s;
}




void I_cImageButton::AddPicture(SDL_Rect pos, SDL_Texture *tex)
{
	PICTURE pic;
	pic.tex = tex;
	pic.rect = pos;

   

	vPictureList.push_back(pic);
}


void I_cImageButton::ClearPictures(void)
{
	vPictureList.clear();
}



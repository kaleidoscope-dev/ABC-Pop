#include "I_cTextBar.h"
#include "I_cAssetmanager.h"
#include "letterdef.h"
#include "anduin/anduin.h"

I_cTextBar::I_cTextBar()
{
}

I_cTextBar::~I_cTextBar()
{
}




void I_cTextBar::Init(string txt, SDL_Texture *image, SDL_Texture *background)
{
    int gap = GAMEAPI_GetPercentage(4, GAMEAPI_WINDOW_W);
	int letter_size = GAMEAPI_GetPercentage(7, GAMEAPI_WINDOW_W);
	int img_x = GAMEAPI_GetPercentage(8, GAMEAPI_WINDOW_W);
	int img_y = GAMEAPI_GetPercentage(72, GAMEAPI_WINDOW_H);
	


	int x = GAMEAPI_GetPercentage(5, GAMEAPI_WINDOW_W);
	int y = GAMEAPI_GetPercentage(90, GAMEAPI_WINDOW_H);
	int w = GAMEAPI_GetPercentage(90, GAMEAPI_WINDOW_W);
	int h = GAMEAPI_GetPercentage(10, GAMEAPI_WINDOW_H);



	// position is relative to parent win
	posx_ = GAMEAPI_GetPercentage(50, w) + x;
	posy_ = GAMEAPI_GetPercentage(50, h) + y;

	// centriraj text
	posx_ = posx_ - (txt.size() * letter_size) / 2;
	posy_ = posy_ - letter_size / 2;


	panel_rect_.x = posx_ - letter_size;
	panel_rect_.y = y;
	panel_rect_.w = (txt.size() * letter_size) + letter_size *2;
	panel_rect_.h = h;


	animal_rect_.w = GAMEAPI_GetPercentage(20, GAMEAPI_WINDOW_W);
	animal_rect_.h = GAMEAPI_GetPercentage(20, GAMEAPI_WINDOW_W);
	animal_rect_.y = panel_rect_.y - animal_rect_.h + (animal_rect_.h/6);
	animal_rect_.x = (GAMEAPI_WINDOW_W / 2) - animal_rect_.w/2;

 
 tex_animal_ = image;
 tex_background = background;

 txt_ = txt;

 for (size_t c = 0; c < txt.size(); c++)
     {
	  I_cText ctext;
	  string s = txt.substr(c,1);

	  ctext.SetLetterProperties(s, posx_ + c * letter_size, posy_, letter_size, letter_size, GAMEAPI_GetColor(255, 0, 0)); // iscrtaj text

	  vLetterList.push_back(ctext);
	 }


}



void I_cTextBar::Reinit(void)
{
	int gap = GAMEAPI_GetPercentage(4, GAMEAPI_WINDOW_W);
	int letter_size = GAMEAPI_GetPercentage(7, GAMEAPI_WINDOW_W);
	int img_x = GAMEAPI_GetPercentage(8, GAMEAPI_WINDOW_W);
	int img_y = GAMEAPI_GetPercentage(72, GAMEAPI_WINDOW_H);

 
 vLetterList.clear(); // TODO: memory


  Reset();

 for (size_t c = 0; c < txt_.size(); c++)
 {
	 I_cText ctext;

	 string s = txt_.substr(c, 1);
	 ctext.SetLetterProperties(s, posx_ + c * letter_size, posy_, letter_size, letter_size, GAMEAPI_GetColor(0, 255, 0)); // iscrtaj text
	 vLetterList.push_back(ctext);
 }

}


void I_cTextBar::Draw(void)
{

	SDL_RenderCopy(AndUIn::renderer_, tex_background, NULL, &panel_rect_);
	SDL_RenderCopy(AndUIn::renderer_, tex_animal_, NULL, &animal_rect_);


	for (int c = 0; c < vLetterList.size(); c++)
	{
		I_cText *text = &vLetterList[c];
		text->Draw();
	}




}



void I_cTextBar::Update(string letter)
{

	for (size_t c = 0; c < vLetterList.size(); c++)
	    {
		 I_cText* text = &vLetterList[c];

		 if (text->GetString() == letter)
		    {
             if (text->drawType_ == DRAW_LETTER_UNKNOWN || text->drawType_ == DRAW_QUESTION)
                {
                 text->drawType_ = DRAW_LETTER_KNOWN;

		 	     if (CheckLevelComplete() == true)
                    {
			         GAMEAPI_CallEvent(GAMEAPI_EVENT_LEVEL_COMPLETE, 0);
			         return;
                    }
                 return;  
                }
		    }
	    }
}



bool I_cTextBar::CheckLevelComplete(void)
{
    for (size_t c = 0; c < vLetterList.size(); c++)
	    {
		 I_cText *text = &vLetterList[c];

		 if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1) 
		    {
			 if (text->drawType_ == DRAW_LETTER_UNKNOWN)
			     return false;
			}else {
                   if (text->drawType_ == DRAW_QUESTION) 
			       return false;
			      }
	    }

 return true;
}






bool I_cTextBar::ContainsLetter(string letter)
{
	vector <string>vtmp;

	for (size_t c = 0; c < vLetterList.size(); c++)
	    {
		 I_cText *text = &vLetterList[c];

		 if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
		    {
			 if (text->drawType_ == DRAW_LETTER_UNKNOWN) //anyone else letter?
			 	 vtmp.push_back(text->GetString());
		    }else {
			       if (text->drawType_ == DRAW_QUESTION) // no?
				       vtmp.push_back(text->GetString());
                  }
            
		}
	
    size_t count = vtmp.size();
    for (size_t c=0;c<count;c++) 
	    {
	     if (vtmp[c] == letter)
		     return true;
		}

 return false;
}


// If anyone's left, create a new one
string I_cTextBar::GetRandomTextBarLetter(void)
{
 vector <string>vtmp;

	for (size_t c = 0; c < vLetterList.size(); c++)
	    {
		 I_cText *text = &vLetterList[c];
         if (text->drawType_ == DRAW_LETTER_UNKNOWN || text->drawType_ == DRAW_QUESTION)
             vtmp.push_back(text->GetString());
	    }



	if (vtmp.size() > 0)
	   {
	    int r = rm->IRandom(0, vtmp.size() -1);
		return vtmp[r];
 	   }

 return "";
}



void I_cTextBar::Reset(void)
{
    size_t count = vLetterList.size();
	for (size_t c = 0; c < count; c++)
	    {
	     I_cText *ptr_txt = &vLetterList[c];


		 if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
			 ptr_txt->drawType_ = DRAW_LETTER_UNKNOWN;
		 else ptr_txt->drawType_ = DRAW_QUESTION;
	    }

}

#include "I_cTextBoxInput.h"



I_cTextBoxInput::I_cTextBoxInput()
{
}


I_cTextBoxInput::~I_cTextBoxInput()
{
}



// WTF?
// TODO:
void I_cTextBoxInput::HandleEvent(SDL_Event *event)
{
 switch (event->type)
        {
		 case SDL_KEYDOWN:
		 {
		  if  (event->key.keysym.sym == SDLK_RETURN)
	          {
			   SetFocus(false);

			   return;
			  }else if (event->key.keysym.sym == SDLK_BACKSPACE)
			           {
					    if (txt_.size() > 0)
						   {
							txt_.erase(txt_.end()-1);

						   }     
					   } else {
							   int vel = (int)txt_.length() * 4;
							   if (vel < widget_rect_.w/2 - 20)
								  {
								   char ch = event->key.keysym.sym;
								   AddLetter(ch);

								  }
						  	  }
		  break;
		}
	 }
 
 I_cTextBox::HandleEvent(event);
}

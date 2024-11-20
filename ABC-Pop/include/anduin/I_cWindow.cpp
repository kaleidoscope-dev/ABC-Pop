#include "I_cWindow.h"
#include "I_cButton.h"


I_cWindow::I_cWindow()
{
 tex_fade_ = NULL;
 Init("Anduin Window");
}



I_cWindow::I_cWindow(std::string name)
{
 Init(name);
}

void I_cWindow::Init(std::string name)
{
	inFocus_ = false;
	tex_window_ = NULL;
	name_ = name;
	fadeIn_ = true;
	alpha_ = 255;
	fadeActive_ = true;
	

	// fade masks
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface *surf = SDL_CreateRGBSurface(0, AndUIn::ANDUIN_Window_W, AndUIn::ANDUIN_Window_H, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surf,NULL, 0xff000000); // TODO: relative to masks
	tex_fade_ = SDL_CreateTextureFromSurface(AndUIn::renderer_,surf);
	SDL_FreeSurface(surf);

}



I_cWindow::~I_cWindow()
{
 int count = GetControlCount();
 for (int c=0;c<count;c++)
     {
	  I_cWidget *wdg = vWidgetList[c];
	 
	  delete wdg;
	 }

	vWidgetList.clear();

    if (tex_fade_)
       {
        SDL_DestroyTexture(tex_fade_);
       }
}





void I_cWindow::OnShow(void)
{
	if (fadeActive_)
	   {
        fadeIn_ = true;
        fadeOut_ = false;
		
	   }

}

void I_cWindow::OnClose(void)
{
	if (fadeActive_)
	   {
        Fadeout();
        fadeIn_ = false;
        fadeOut_ = true;
       }
}


void I_cWindow::SetActive(bool f)
{
 inFocus_ = f;
 

 if (inFocus_ == false)
    {
     OnClose();
	}else {
           
           OnShow();
          }
}

void I_cWindow::AddWidget(I_cWidget *widget)
{
 vWidgetList.push_back(widget);
}


void I_cWindow::RemoveWidget(I_cWidget *ptr_widget)
{
 for (size_t c=0;c<vWidgetList.size();c++)
     {
      if (vWidgetList[c] == ptr_widget) 
         {
          vWidgetList.erase(vWidgetList.begin() + c);
         }
     }
}


void I_cWindow::Draw(void)
{

  if (tex_window_)
      SDL_RenderCopy(AndUIn::renderer_, tex_window_, NULL, NULL);

  size_t count = vWidgetList.size();

	  // mozda staviti iterator. 
  for (size_t c = 0; c < count; c++)
	  {
	   I_cWidget *wdg = vWidgetList[c];
	    wdg->Draw();
	  }

 if (fadeActive_ && fadeIn_)
     Fadein2();
  

}




// od crne
void I_cWindow::Fadein2(void)
{
 if (alpha_ >= 4)
    {
     alpha_ -= 4;

	 SDL_SetTextureAlphaMod(tex_fade_, alpha_);
	 SDL_RenderCopy(AndUIn::renderer_, tex_fade_, NULL, NULL);
	 //SDL_RenderPresent(AndUIn::renderer_);


    }else {
           alpha_ = 255;
           fadeIn_ = false;
          }
}

// DEPRECATED:
void I_cWindow::Fadeout2(void)
{
/*
 if (alpha_ <=250)
    {
     SDL_Delay(2);
     alpha_ += 4;
    
     SDL_SetTextureAlphaMod(tex_fade_, alpha_);
 	 SDL_RenderCopy(AndUIn::renderer_, tex_fade_, NULL, NULL);
	 //L_RenderPresent(AndUIn::renderer_);
      //printf("%d\n",alpha_);
	}else {
           alpha_ = 0;
           fadeOut_ = false;
          }
          */


}



// DEPRECATED:
void I_cWindow::Fadein(void)
{
/*
 if (!fadeActive_) 
     return;

        Draw();
	    SDL_RenderPresent(AndUIn::renderer_);
 
 for (int alpha_ = 255; alpha_ >= 2; alpha_-=2)
     {
        SDL_Delay(2);
	    SDL_SetTextureAlphaMod(tex_fade_, alpha_);
	    SDL_RenderCopy(AndUIn::renderer_, tex_fade_, NULL, NULL);
	    SDL_RenderPresent(AndUIn::renderer_);
        printf("%d\n",alpha_);
       }


       alpha_ = 0;
       */
}


// to black
void I_cWindow::Fadeout(void)
{
 if (!fadeActive_)
      return;


 for (int alpha_ = 0; alpha_ <= 250; alpha_+=4)
     {
      Draw();
	  SDL_SetTextureAlphaMod(tex_fade_, alpha_);
	  SDL_RenderCopy(AndUIn::renderer_, tex_fade_, NULL, NULL);
	  SDL_RenderPresent(AndUIn::renderer_);
	  SDL_Delay(2);  // block any input here 
	}

 alpha_ = 255;

}


void I_cWindow::SetFadeActive(bool active)
{
 fadeActive_ = active;

}





int I_cWindow::GetControlCount(void)
{
 return (int)vWidgetList.size();
}

I_cWidget *I_cWindow::GetControl(int num)
{
 return vWidgetList[num];
}



I_cWidget *I_cWindow::GetControl(SDL_Event *event)
{

	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	SDL_Point pt = { x,y };

	size_t count = vWidgetList.size();
	for (size_t c = 0; c < count; c++)
	    {
		  I_cWidget *wdg = vWidgetList[c];

	     if (SDL_PointInRect(&pt, &wdg->widget_rect_))
		     {
		      return wdg;
			  }
	    }
 return NULL;
}



void I_cWindow::SetBackgroundTexture(SDL_Texture *tex)
{
 this->tex_window_ = tex;
}


void I_cWindow::SetActiveWidget(I_cWidget *wdg)
{
	size_t count = vWidgetList.size();
	for (size_t c = 0; c < count; c++)
	{
		I_cWidget *ptr_wdg = vWidgetList[c];
		if (ptr_wdg != wdg)
		    wdg->SetFocus(false);
			 else ptr_wdg->SetFocus(true);
	}

}



void I_cWindow::DefocusAll(void)
{
	size_t count = vWidgetList.size();
	for (size_t c = 0; c < count; c++)
	{
		I_cWidget *ptr_wdg = vWidgetList[c];
		ptr_wdg->SetFocus(false);
	}
}







void I_cWindow::HandleEvent(SDL_Event* event)
{


	switch (event->type)
	{
	case SDL_MOUSEBUTTONUP:
	{
		I_cWidget* wdg = GetControl(event);
		DefocusAll();

		if (wdg)
		{
			wdg->HandleEvent(event);
			event->type = SDL_FIRSTEVENT;  //  NOTE: Has to be here bacause fastdelages autorepease onClick. TODO: Checkcheck SDL autorepease
		}
		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	{
		I_cWidget* wdg = GetControl(event);
		DefocusAll();

		if (wdg)
		{
			wdg->HandleEvent(event);   // NOTE: but not here
		}
		break;
	}

	case SDL_KEYDOWN:
	{
		if (event->key.repeat == 0)
		{
			I_cWidget* wdg = GetControl(event);

			if (wdg)
			{
				wdg->HandleEvent(event);
			}
		}

		break;
	}


	}

}


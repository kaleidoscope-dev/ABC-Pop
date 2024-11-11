#include "I_cText.h"
#include <math.h>
#include "I_cAssetmanager.h"

I_cText::I_cText()
{
    drawUnknown_ = false;
    show_ = true;
}


I_cText::~I_cText()
{
}


// FFS: feractor
void I_cText::Draw(void)
{
 SDL_Rect loc = { posx,posy,width,height };


 if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
    {
     switch (drawType_)
            {
             case DRAW_LETTER_UNKNOWN:
               RenderLetter(texLetterClr1_, &loc);
               break;

             case DRAW_LETTER_KNOWN:
               RenderLetter(texLetterClr2_, &loc);
               break;


             case DRAW_QUESTION:
               RenderLetter(texQuestion_,&loc);
               break;
             case DRAW_EMPTY:
               break;
            }
    }else {
             switch (drawType_)
                    {
                     case DRAW_LETTER_UNKNOWN:
                       RenderLetter(texLetterClr1_, &loc);
                       break;

                     case DRAW_LETTER_KNOWN:
                       RenderLetter(texLetterClr1_, &loc);
                       break;


                     case DRAW_QUESTION:
                       RenderLetter(texQuestion_,&loc);
                       break;
                     case DRAW_EMPTY:
                       break;
                    }
          }

}



void I_cText::SetShow(bool b)
{ 
 show_ = b;
}



void I_cText::SetLetterProperties(string txt, int x, int y, int w, int h, SDL_Color clr)
{
 posx = x;
 posy = y;
 width = w;
 height = h;

 text_string = txt;
  if (text_string.empty())
 	  text_string = " ";



 if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
    {
     drawType_ = DRAW_LETTER_UNKNOWN;
     texLetterClr1_ = CreateLetterTex(txt,x,y, GAMEAPI_GetColor(0, 255, 0));
     texLetterClr2_ = CreateLetterTex(txt,x,y, GAMEAPI_GetColor(255, 0, 0));
    }else {
           drawType_ = DRAW_QUESTION;
           texLetterClr1_ = CreateLetterTex(txt,x,y, GAMEAPI_GetColor(0, 255, 0));
           texQuestion_ = CreateLetterTex("?", x, y, GAMEAPI_GetColor(255, 0, 0));
          }

}



SDL_Texture *I_cText::CreateLetterTex(string letter, int x, int y, SDL_Color clr)
{
	posx = x;
	posy = y;

	if (letter.empty())
	    return NULL; 

    // color / outline
	SDL_Color white = { 0xFF, 0xFF, 0xFF };
	SDL_Color black = { 0x00, 0x00, 0x00 };

	SDL_Surface *bg_surface = TTF_RenderText_Blended(gAssetManager->GetFontOutline(), letter.c_str(), black);
	SDL_Surface *fg_surface = TTF_RenderText_Blended(gAssetManager->GetFont(), letter.c_str(), clr);
	SDL_Rect rect = { 2, 2, fg_surface->w, fg_surface->h };


	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);


	SDL_Texture *tex = SDL_CreateTextureFromSurface(gAssetManager->GetRenderer(), bg_surface); //now you can convert it into a texture

	SDL_FreeSurface(fg_surface);
	SDL_FreeSurface(bg_surface);

	return tex;
}





string I_cText::GetString(void)
{
 return text_string;
}


void I_cText::SetString(string s)
{
 text_string = s;
}


void I_cText::SetPosition(int x, int y)
{
 posx = x;
 posy = y;
}


void I_cText::RenderLetter(SDL_Texture *tex, SDL_Rect *location)
{

	SDL_RenderCopy(gAssetManager->GetRenderer(), tex, NULL, location);
}



SDL_Texture *I_cText::GetTextTexture(void)
{
 return texLetterClr1_;
}




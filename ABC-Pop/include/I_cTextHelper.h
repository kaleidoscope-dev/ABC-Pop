#pragma once
#include "gameapi.h"

class I_cTextHelper
{
 public:
	 I_cTextHelper();
	   ~I_cTextHelper();


		 SDL_Texture *GetTextTexture(string text);
};
#pragma once
#include "anduin/anduin.h"
#include "gameapi.h"
#include "anduin/I_cButton.h"

class I_cCollectable
{
 public:
			I_cCollectable();
		 ~I_cCollectable();

		 void Draw(bool update);

		  SDL_Texture *tex;

			bool IsClicked(int mx, int my);

            float posx;
			SDL_Rect rect_;

			void wavefunc(void);
};
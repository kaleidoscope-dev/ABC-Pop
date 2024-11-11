#pragma once
#include "gameapi.h"


class I_cAnimalBar
{
 public:
	 I_cAnimalBar();
	   ~I_cAnimalBar();

	   void Init(SDL_Texture *ani1, SDL_Texture *ani2);
     void Draw();

		 

 private:
  SDL_Texture *tex_animal1;
	SDL_Texture *tex_animal2;
	
	
 int ANIMAL_SIZE;
};
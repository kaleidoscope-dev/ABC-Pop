#include "I_cAnimalBar.h"
#include "I_cAssetmanager.h"





I_cAnimalBar::I_cAnimalBar()
{
}

I_cAnimalBar::~I_cAnimalBar()
{
}




void I_cAnimalBar::Init(SDL_Texture *ani1, SDL_Texture *ani2)
{
	ANIMAL_SIZE = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
 
 tex_animal1 = ani1;
 tex_animal2 = ani2;
}

void I_cAnimalBar::Draw()
{
 if (tex_animal1)
    {
	   SDL_Rect rct = GAMEAPI_GetRect(10, ANIMAL_SIZE, ANIMAL_SIZE, ANIMAL_SIZE);
	   SDL_RenderCopy(gAssetManager->GetRenderer(), tex_animal1, NULL, &rct);
    }
  

 if (tex_animal2)
 {
	 SDL_Rect rct = GAMEAPI_GetRect(10, ANIMAL_SIZE*2 +10, ANIMAL_SIZE, ANIMAL_SIZE);
	 SDL_RenderCopy(gAssetManager->GetRenderer(), tex_animal2, NULL, &rct);
 }


 //switch (numLives_)
 //       {
	//			 case 0:
	//			 {
	//				 for (int c = 0; c < 3; c++)
	//				 {
	//					 SDL_Rect rct = GAMEAPI_GetRect(c * 45 + 10, 10, STAR_SIZE, STAR_SIZE);
	//					 SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGray(), NULL, &rct);
	//				 }
	//				 break;
	//			 }

     
}





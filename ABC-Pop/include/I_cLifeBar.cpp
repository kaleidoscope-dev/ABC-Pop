#include "I_cLifeBar.h"
#include "I_cAssetmanager.h"





I_cLifeBar::I_cLifeBar()
{
}

I_cLifeBar::~I_cLifeBar()
{
}




void I_cLifeBar::Init(void)
{
 numLives_ = MAX_LIVES;
 posx_ = 10;
 posy_ = 10;
 STAR_SIZE = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W,8);
}

void I_cLifeBar::AddLife(void)
{
}


void I_cLifeBar::SetLives(int lives)
{
 numLives_ = lives;
}


int I_cLifeBar::RemoveLife(void)
{
 if (numLives_ > 0)
	numLives_--;

 return numLives_;
}


void I_cLifeBar::SetPos(int x, int y)
{
 posx_ = x;
 posy_ = y;
}


void I_cLifeBar::Draw()
{
 switch (numLives_)
        {
				 case 0:
				 {
					 for (int c = 0; c < 3; c++)
					 {
						 SDL_Rect rct = GAMEAPI_GetRect(c * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
						 SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGray(), NULL, &rct);
					 }
					 break;
				 }

				 case 1:
				 {
					 int c = 0;
					 SDL_Rect rct = GAMEAPI_GetRect(0 * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
					 SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGold(), NULL, &rct);

					 rct = GAMEAPI_GetRect(1 * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
					 SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGray(), NULL, &rct);

					 rct = GAMEAPI_GetRect(2 * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
					 SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGray(), NULL, &rct);

					 break;
				 }
				 case 2:
				 {
				  int c=0;
					SDL_Rect rct;
					for (c = 0; c < numLives_; c++)
					    {
					     rct = GAMEAPI_GetRect(c * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
						   SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGold(), NULL, &rct);
					    }

					rct = GAMEAPI_GetRect(c * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
					SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGray(), NULL, &rct);
					break;
				 }


				 case 3:
				 {
					for (int c = 0; c < numLives_; c++)
					    {
						   SDL_Rect rct = GAMEAPI_GetRect(c * STAR_SIZE + posx_, posy_, STAR_SIZE, STAR_SIZE);
					     SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetStarGold(), NULL, &rct);
							}
					break;
				 }
				}// END switch
     
}


int I_cLifeBar::GetStarCount(void)
{
 return numLives_;
}



void I_cLifeBar::Reset(void)
{
	numLives_ = MAX_LIVES;
}

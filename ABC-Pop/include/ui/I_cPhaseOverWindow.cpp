#include "I_cPhaseOverWindow.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"
#include "include/letterdef.h"


I_cPhaseOverWindow::I_cPhaseOverWindow()
{
}


I_cPhaseOverWindow::~I_cPhaseOverWindow()
{
 for (size_t c=0;c< vLetterList.size();c++)
     {
      LETTER *ptr_letter = &vLetterList[c];
      SDL_DestroyTexture(ptr_letter->texLetter);
      SDL_DestroyTexture(ptr_letter->texQuestion);
     }
}


void I_cPhaseOverWindow::Draw()
{
	I_cWindow::Draw();


   for (int c=0;c<vLetterList.size();c++)
       {
        if (vLetterList[c].question)
             SDL_RenderCopy(gAssetManager->GetRenderer(), vLetterList[c].texQuestion, NULL, &vLetterList[c].loc);
        else SDL_RenderCopy(gAssetManager->GetRenderer(), vLetterList[c].texLetter, NULL, &vLetterList[c].loc);
      }


}




void I_cPhaseOverWindow::OnShow(void)
{
   I_cWindow::Draw();

   for (int c=0;c<LETTER_Z;c++)
       {
        SDL_RenderCopy(gAssetManager->GetRenderer(), vLetterList[c].texLetter, NULL, &vLetterList[c].loc);
       }


   for (int c=0;c<vPictureList.size();c++)
       {
        SDL_Delay(50);
        I_cPicture* ptr_pic = vPictureList[c];
        ptr_pic->SetShow(true);
        Draw();
        SDL_RenderPresent(AndUIn::renderer_);
       }


     
   for (int c=0;c<LETTER_Z;c++)
       {
        SDL_Delay(50);
        vLetterList[c].question = true;
        Draw();
        SDL_RenderPresent(AndUIn::renderer_);
       }
}


void I_cPhaseOverWindow::Init(void)
{

   int world = GAMEAPI_GetRandom(0,4);
   SetBackgroundTexture(gAssetManager->GetLevelBackground((GAMEAPI_WORLD_TYPE)world));  // NOTE: always the current world


   pic_frame = new I_cPicture();
   pic_panel = new I_cPicture();
   pic_letter_back = new I_cPicture();


   pic_frame->SetTexture(gAssetManager->GetStatFrame());
   pic_panel->SetTexture(gAssetManager->GetGoldFrame());
   pic_letter_back->SetTexture(gAssetManager->GetTextbarPanel());

   AddWidget(pic_frame);
   AddWidget(pic_panel);


   butt_continue = new I_cButton();
   butt_continue->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
   butt_continue->SetTransparent(true);
   
   butt_continue->OnClick.bind(this, &I_cPhaseOverWindow::OnContinue);
   AddWidget(butt_continue);


   int frame_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
   int frame_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 90);
   int gap_size_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
   int gap_size_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 5);


   pic_panel->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
   pic_frame->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);


   int panel_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
   int panel_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 77);
   int panel_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 75);
   int panel_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 13);
   pic_letter_back->SetPos(panel_x, panel_y, panel_w, panel_h);
   AddWidget(pic_letter_back);


   int star_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
   int star_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);
   int star_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 12);
   int star_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 12);

   I_cPicture* pic_star1 = new I_cPicture();
   I_cPicture* pic_star2 = new I_cPicture();
   I_cPicture* pic_star3 = new I_cPicture();


   pic_star1->SetTexture(gAssetManager->GetStarGold());
   pic_star1->SetPos(star_x - star_w * 2, star_y + star_h/2, star_w, star_h);
   AddWidget(pic_star1);

   pic_star2->SetTexture(gAssetManager->GetStarGold());
   pic_star2->SetPos(star_x - star_w/2, star_y, star_w, star_h);
   AddWidget(pic_star2);


   pic_star3->SetTexture(gAssetManager->GetStarGold());
   pic_star3->SetPos(star_x + star_w, star_y + star_h/2, star_w, star_h);
   AddWidget(pic_star3);


   int animal_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 3);
   int animal_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 13);
   int animal_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 12);
   int animal_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);

   int start_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);

   for (int c = 0; c < WORLD_COUNT; c++)
       {
        for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
            {
             int posx = (animal_x + animal_w * (i+1));
             int posy = start_y + (animal_y + animal_h * (c+1));

             I_cPicture* pic = new I_cPicture();
             pic->SetTexture(gAssetManager->GetAnimal(c, i));
             pic->SetPos(posx, posy, animal_w, animal_h);
             pic->SetShow(false);
             AddWidget(pic);
             vPictureList.push_back(pic);
            }
       }




   int letter_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 17);
   int letter_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 75);
   int letter_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
   int letter_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
   int posx, posy = 0;
   start_y = GAMEAPI_GetPercentage(panel_h, 20);

   int let = 0;
   for (int c = 0; c < 12; c++)
       {
        for (int i = 0; i < 2; i++)
            {
             int posx = letter_x + letter_w * (c+1);
             int posy = start_y + (letter_y + letter_h * (i+1));


             LETTER lett;
             lett.question = false;
             lett.texLetter = GAMEAPI_GetStringTexture(letterIndexName[let++].name, AndUIn::Green);
             lett.texQuestion = GAMEAPI_GetStringTexture("?", AndUIn::Red);
             lett.loc = GAMEAPI_GetRect(posx, posy, letter_w, letter_h);
             vLetterList.push_back(lett);
            }
       }

}





// change game phsase only if we're not in the paused state
void I_cPhaseOverWindow::OnContinue(void *ptr_data)
{
 if (gGameData.IsGameOver() == true && GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
    {
     GAMEAPI_Phase_ = GAMEAPI_PHASE_2;  // regardless of the currennt phase, on end game  got to phase 2
     gGameData.ResetCounters();
	 gGameData.ChangeGamePhase();
     GAMEAPI_CallEvent(GAMEAPI_EVENT_PHASE_FINISHED, NULL);
     return;
    }

 GAMEAPI_CallEvent(GAMEAPI_EVENT_QUIT_CURRENT_GAME,NULL);

 
}




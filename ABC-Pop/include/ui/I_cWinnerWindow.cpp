#include "I_cWinnerWindow.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"
#include "include/letterdef.h"
#include "include/I_cSoundBlaster.h"


I_cWinnerWindow::I_cWinnerWindow()
{
}


I_cWinnerWindow::~I_cWinnerWindow()
{
 delete pic_frame;
 delete pic_panel;
}


void I_cWinnerWindow::Draw()
{
	I_cWindow::Draw();


    // TODO: DrawBalloons();
	std::list<I_cBalloon*>::iterator it = vBalloonList.begin();
	while (it != vBalloonList.end())
	      {
           I_cBalloon *ptr_balloon = *it;
		   ptr_balloon->Draw();

           if (ptr_balloon->balloon_rect_.y <= 0)
              {
			   ptr_balloon->Pop();
              }

           if (ptr_balloon->balloon_rect_.y < -ptr_balloon->balloon_rect_.h)
			  {
               int r = rm->IRandom(3, 7);
               for (int c=0;c<r;c++)
                   {
                    I_cStarDroplet *drop = new I_cStarDroplet();
                    drop->Init(ptr_balloon->balloon_rect_.x + ptr_balloon->balloon_rect_.w/2 ,ptr_balloon->balloon_rect_.y + ptr_balloon->balloon_rect_.h,AndUIn::White);
                    vStarList.push_back(drop);
                   }

			   it = vBalloonList.erase(it);
			   delete ptr_balloon;
			   ptr_balloon = NULL;


			  }else it++;
		  }


 DrawStars();


 pic_frame->Draw();
 //pic_panel->Draw();

            int pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
         	int pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 20);
         	int size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 80);
         	int size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 5);

 for (size_t c=0;c< vWinnerStringList.size();c++)
     {
      int pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
	  //SDL_Rect location = GAMEAPI_GetRect(50,pos_y + 60*c,GAMEAPI_WINDOW_W-100,50);
      SDL_Rect location = GAMEAPI_GetRect(pos_x,pos_y +  size_h*c,size_w,size_h);
	  //SDL_Rect location = GAMEAPI_GetRect(50,pos_y + 60*c,GAMEAPI_WINDOW_W-100,50);
	  SDL_RenderCopy(gAssetManager->GetRenderer(), vWinnerStringList[c], NULL, &location);
	 }
}


void I_cWinnerWindow::DrawStars(void)
{
	std::list<I_cStarDroplet*>::iterator it = vStarList.begin();
	while (it != vStarList.end())
	      {
           I_cStarDroplet *ptr_star = *it;
		   ptr_star->Draw(); 


           if (ptr_star->star_rect_.y > GAMEAPI_WINDOW_H)
			  {
		       it = vStarList.erase(it);
			   delete ptr_star;
			   ptr_star = NULL;
              }else it++;
          }

}


void I_cWinnerWindow::OnClose(void)
{
  gSoundBlaster.StopMusic();
 SDL_RemoveTimer(timerId_);
}



void I_cWinnerWindow::OnShow(void)
{
  gSoundBlaster.StopAll();
  gSoundBlaster.PlayWinnerMusic();
  timerId_ = SDL_AddTimer(550, &OnTimer_CreateBalloon, this);
}




void I_cWinnerWindow::Init(void)
{
   SetBackgroundTexture(gAssetManager->GetLevelBackground((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld()));  // NOTE: mora biti za na kojem smo svijetu


   pic_frame = new I_cPicture();
   pic_panel = new I_cPicture();


   pic_frame->SetTexture(gAssetManager->GetStatFrame());
   pic_panel->SetTexture(gAssetManager->GetGoldFrame());
   //pic_frame->sethos

   //AddWidget(pic_frame);
   //AddWidget(pic_panel);


   butt_continue = new I_cButton();
   butt_continue->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
   butt_continue->SetTransparent(true);
   
   butt_continue->OnClick.bind(this, &I_cWinnerWindow::OnContinue);
   AddWidget(butt_continue);


   pic_panel->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
   pic_frame->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);



	
	for (size_t c=0;c<GAMEAPI_vWinnerStringList.size();c++)
	    {
	     SDL_Texture *tex = GAMEAPI_GetStringTexture(GAMEAPI_vWinnerStringList[c], AndUIn::White);
		  vWinnerStringList.push_back(tex);
		}
}





// povratak na main menu
void I_cWinnerWindow::OnContinue(void *ptr_data)
{
 GAMEAPI_CallEvent(GAMEAPI_EVENT_QUIT_CURRENT_GAME,NULL);
}




// from: Engine::GAMEAPI_EVENT_CREATE_WINNER_BALLOON
void I_cWinnerWindow::CreateBalloon(void)
{
	I_cBalloon *balloon = new I_cBalloon();
	int i = rm->IRandom(0, GAMEAPI_WINDOW_W);
	int small = rm->IRandom(0, 1);

	balloon->Init(i, GAMEAPI_WINDOW_H+GAMEAPI_BALLOON_H, small);
	vBalloonList.push_back(balloon);
}




// SDL_AddTimer ima problema s multithreadingom, tako da nesmijemo stvarati balone
// direktno sa param->CreateBalloon(), nego moramo zvati event.
Uint32 I_cWinnerWindow::OnTimer_CreateBalloon(Uint32 interval, void *param)
{
 GAMEAPI_CallEvent(GAMEAPI_EVENT_CREATE_WINNER_BALLOON, NULL);
 return(interval);
}

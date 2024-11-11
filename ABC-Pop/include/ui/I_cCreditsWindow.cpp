#include "I_cCreditsWindow.h"

#include "include/gameapi.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"

I_cCreditsWindow::I_cCreditsWindow()
{
}


I_cCreditsWindow::~I_cCreditsWindow()
{
/*
 delete butt_next;
 delete butt_prev;
 //delete tex_stat_panel;
 //delete tex_forest_frame;
 delete pic_frame;
 delete pic_panel;

 for (size_t c = 0; c < vStringList.size(); c++)
	  SDL_DestroyTexture(vStringList[c]);

	   


 vStringList.clear();
 */
}


void I_cCreditsWindow::Init(void)
{
	butt_next = new I_cButton();
	butt_prev = new I_cButton();

	tex_stat_panel = gAssetManager->GetStatFrame();
	tex_forest_frame = gAssetManager->GetGoldFrame();


	pic_frame = new I_cPicture();
	pic_panel = new I_cPicture();



	pic_frame->SetTexture(tex_forest_frame);
	pic_panel->SetTexture(tex_stat_panel);
    pic_frame->SetPos(0,0,GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
    pic_panel->SetPos(0,0,GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);

   	int bt_prevnext_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int bt_prevnext_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);


	butt_prev->SetTexture(gAssetManager->GetArrowLeft(), gAssetManager->GetArrowLeft());
	butt_next->SetTexture(gAssetManager->GetArrowRight(), gAssetManager->GetArrowRight());

	butt_prev->SetPos(10,GAMEAPI_WINDOW_H- bt_prevnext_h -10, bt_prevnext_w, bt_prevnext_h);
	butt_next->SetPos(GAMEAPI_WINDOW_W- bt_prevnext_w -20, GAMEAPI_WINDOW_H - bt_prevnext_h - 10, bt_prevnext_w, bt_prevnext_h);


	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_back_to_options_ = new I_cButton();
	btn_back_to_options_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_back_to_options_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());



	butt_next->OnClick.bind(this, &I_cCreditsWindow::NextCollection);
	butt_prev->OnClick.bind(this, &I_cCreditsWindow::PrevCollection);
	btn_back_to_options_->OnClick.bind(this, &I_cCreditsWindow::OnBackToOptions);

	int frame_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int frame_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 90);
	int gap_size_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int gap_size_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 5);


	//pic_forest_panel->SetPos(gap_size_x * 2, gap_size_y * 2, frame_w, frame_h);
	pic_panel->SetPos(0,0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);


	AddWidget(pic_panel);
	AddWidget(pic_frame);

	AddWidget(butt_next);
	AddWidget(butt_prev);

	AddWidget(btn_back_to_options_);
	current_window_ = WORLD_FOREST;


	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));

	
	for (size_t c=0;c<GAMEAPI_vArtistStringList.size();c++)
	    {
	     SDL_Texture *tex = GAMEAPI_GetStringTexture(GAMEAPI_vArtistStringList[c], AndUIn::White);
		  //SDL_Texture *tex = GAMEAPI_GetTextTexture("TODO: ");
		  vArtistStringList.push_back(tex);
		 }

   for (size_t c = 0; c < GAMEAPI_vCreditsStringList.size(); c++)
       {
        SDL_Texture* tex = GAMEAPI_GetStringTexture(GAMEAPI_vCreditsStringList[c], AndUIn::White);
        //SDL_Texture *tex = GAMEAPI_GetTextTexture("TODO: ");
        vCreditsStringList.push_back(tex);
       }
			

}


void I_cCreditsWindow::OnBackToOptions(void *ptr_data)
{
 GAMEAPI_CallEvent(GAMEAPI_EVENT_SHOW_OPTIONS,NULL);
}

void I_cCreditsWindow::Draw(void)
{
 I_cWindow::Draw();


           int pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
         	int pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 20);
         	int size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 80);
         	int size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 5);
 if (current_window_ %2)
    {
     for (size_t c=0;c< vArtistStringList.size();c++)
         {


		    SDL_Rect location = GAMEAPI_GetRect(pos_x,pos_y +  size_h*c,size_w,size_h);
	       SDL_RenderCopy(gAssetManager->GetRenderer(), vArtistStringList[c], NULL, &location);
		   }
    }else {
           for (size_t c = 0; c < vCreditsStringList.size(); c++)
               {
                int pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
                SDL_Rect location = GAMEAPI_GetRect(pos_x,pos_y +  size_h*c,size_w,size_h);
                SDL_RenderCopy(gAssetManager->GetRenderer(), vCreditsStringList[c], NULL, &location);
               }
          }


}





void I_cCreditsWindow::NextCollection(void *ptr_data)
{
	current_window_++;
	if (current_window_ > WORLD_COUNT - 1)
		current_window_ = 0;


	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}


void I_cCreditsWindow::PrevCollection(void *ptr_data)
{
	current_window_--;
	if (current_window_ < 0)
		current_window_ = WORLD_COUNT - 1;


	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}


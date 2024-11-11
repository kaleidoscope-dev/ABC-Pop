#include "I_cResetMessageWindow.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"
#include "include/I_cSoundBlaster.h"

I_cResetMessageWindow::I_cResetMessageWindow()
{
}


I_cResetMessageWindow::~I_cResetMessageWindow()
{
}


void I_cResetMessageWindow::Draw()
{
   I_cWindow::Draw();

   int p_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
   int p_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 80);
   int p_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
   for (size_t c = 0; c < vMessageList.size(); c++)
   {
      SDL_Rect location = GAMEAPI_GetRect(p_x, p_y + 60 * c, p_w, 50);
      SDL_RenderCopy(gAssetManager->GetRenderer(), vTexList[c], NULL, &location);
   }


}


void I_cResetMessageWindow::CreateBackButton()
{
   int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
   int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


   SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

   btn_return_ = new I_cButton(); // back to main menu

   btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
   btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


   btn_return_->OnClick.bind(this, &I_cResetMessageWindow::OnReturn);  // back to main menu from credits window
   AddWidget(btn_return_);
}



void I_cResetMessageWindow::Init(void)
{

  


   btn_ok_ = new I_cButton();
   panel = new I_cPicture();

   panel->SetTexture(gAssetManager->GetPanelMsgBlue());

	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 70);
	int music_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int music_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);


	SDL_Rect rc_ok = { bt_pos_x,bt_pos_y, bt_w, bt_h };

	int bln_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);


   btn_ok_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_RED, true), gAssetManager->GetUIButton(BUTTON_COLOR_RED, false));
   btn_ok_->SetPos(rc_ok.x, rc_ok.y, rc_ok.w, rc_ok.h);
   btn_ok_->SetText("Reset", GAMEAPI_GetColor(0, 120, 0));
   btn_ok_->SetUsingFonts(true);
   btn_ok_->SetShowText(true);


   int p_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
   int p_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 27);
   int p_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
   //int p_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 20);

   int p_h = p_x + 200 + 40;


   SDL_Rect rc_panel = {p_x, p_y, p_w, p_h};

   panel->SetPos(p_x, p_y, p_w, p_h);



	int world = GAMEAPI_GetRandom(0, 4);
	int ani = GAMEAPI_GetRandom(0, 5);
	int ani_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

	// main menu ce uvijek imati random pozadinu prilikom starta
	GAMEAPI_WORLD_TYPE rnd_background = (GAMEAPI_WORLD_TYPE)rm->IRandom(0, 4);
	SetBackgroundTexture(gAssetManager->GetWorldBackground(rnd_background));


   CreateBackButton();

   btn_ok_->OnClick.bind(this, &I_cResetMessageWindow::OnOk);   //  Show World Select Menu



	AddWidget(btn_ok_);
   AddWidget(panel);



   string str1 = "  This action will reset all of game data    ";
   string str2 = "         And the game will close.            ";
   string str3 = "Press Reset To Continue or Back button to return.";

   vMessageList.push_back(str1);
   vMessageList.push_back(str2);
   vMessageList.push_back(str3);

   for (size_t c = 0; c < vMessageList.size(); c++)
   {
      SDL_Texture* tex = GAMEAPI_GetStringTexture(vMessageList[c], AndUIn::White);
      //SDL_Texture *tex = GAMEAPI_GetTextTexture("TODO: ");
      vTexList.push_back(tex);
   }

}



void I_cResetMessageWindow::OnOk(void* ptr_data)
{
 gGameData.ResetGameData();

 
 GAMEAPI_CallEvent(GAMEAPI_EVENT_QUIT_GAME, NULL);
}


void I_cResetMessageWindow::OnReturn(void *ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_SETTINGS_SELECT;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);


}



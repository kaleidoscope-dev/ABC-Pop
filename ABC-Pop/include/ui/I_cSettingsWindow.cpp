#include "I_cSettingsWindow.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"
#include "include/I_cSoundBlaster.h"

I_cSettingsWindow::I_cSettingsWindow()
{
}


I_cSettingsWindow::~I_cSettingsWindow()
{
}


void I_cSettingsWindow::Draw()
{
 I_cWindow::Draw();
}


void I_cSettingsWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_return_ = new I_cButton(); // back to main menu

	btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_return_->OnClick.bind(this, &I_cSettingsWindow::OnReturn);  // back to main menu from credits window
   AddWidget(btn_return_);
}


void I_cSettingsWindow::Init(void)
{

  


	btn_music_ = new I_cCheckButton();
	btn_sfx_ = new I_cCheckButton();
	//btn_sfx_ = new I_cButton();
	btn_reset_game_ = new I_cButton();
	btn_credits_ = new I_cButton();

	CreateBackButton();

	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);
	int music_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int music_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);

	SDL_Rect rc_music = { GAMEAPI_WINDOW_W/2-music_w/2,bt_pos_y  ,  music_w,music_h };
	SDL_Rect rc_sfx_ = { GAMEAPI_WINDOW_W / 2 - music_w / 2,bt_pos_y + music_h  ,  music_w,music_h };

	SDL_Rect rc_reset = { bt_pos_x,bt_pos_y + bt_h * 2, bt_w, bt_h };
	SDL_Rect rc_credits = { bt_pos_x,bt_pos_y + bt_h * 3, bt_w, bt_h };

	int bln_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

	btn_music_->SetPos(rc_music.x, rc_music.y, rc_music.w, rc_music.h);
	btn_music_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
	btn_music_->SetCheckTexture(gAssetManager->GetMusicOff(), gAssetManager->GetMusicOn());

	btn_sfx_->SetPos(rc_sfx_.x, rc_sfx_.y, rc_sfx_.w, rc_sfx_.h);
	btn_sfx_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_BLUE, true), gAssetManager->GetUIButton(BUTTON_COLOR_BLUE, false));
	btn_sfx_->SetCheckTexture(gAssetManager->GetSfxOff(), gAssetManager->GetSfxOn());


	btn_reset_game_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_RED, true), gAssetManager->GetUIButton(BUTTON_COLOR_RED, false));
	btn_reset_game_->SetPos(rc_reset.x, rc_reset.y, rc_reset.w, rc_reset.h);
	btn_reset_game_->SetText("Reset Game", GAMEAPI_GetColor(0, 120, 0));
	btn_reset_game_->SetUsingFonts(true);
	btn_reset_game_->SetShowText(true);


	btn_credits_->SetPos(rc_credits.x, rc_credits.y, rc_credits.w, rc_credits.h);
	btn_credits_->SetText("Credits", GAMEAPI_GetColor(0, 0, 0));
	btn_credits_->SetUsingFonts(true);
	btn_credits_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_YELLOW, true), gAssetManager->GetUIButton(BUTTON_COLOR_YELLOW, false));
	btn_credits_->SetShowText(true);


	//btn_show_credits_->SetText("   Credits   ", GAMEAPI_GetColor(255, 255, 255));
	//btn_show_credits_->SetPos(rc_credits.x, rc_credits.y, rc_credits.w, rc_credits.h);
	//btn_show_credits_->SetUsingFonts(true);




	int world = GAMEAPI_GetRandom(0, 4);
	int ani = GAMEAPI_GetRandom(0, 5);
	int ani_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

	// main menu ce uvijek imati random pozadinu prilikom starta
	GAMEAPI_WORLD_TYPE rnd_background = (GAMEAPI_WORLD_TYPE)rm->IRandom(0, 4);
	SetBackgroundTexture(gAssetManager->GetWorldBackground(rnd_background));



	btn_music_->OnClick.bind(this, &I_cSettingsWindow::OnMusicOnOff);        //  Quit Gane
	btn_sfx_->OnClick.bind(this, &I_cSettingsWindow::OnSfxOnOff);    // Show Collections window


	btn_credits_->OnClick.bind(this, &I_cSettingsWindow::OnShowCredits);   //  Show World Select Menu
	btn_reset_game_->OnClick.bind(this, &I_cSettingsWindow::OnResetGame); // Reset game iz main menu



	AddWidget(btn_music_);
	AddWidget(btn_sfx_);
	AddWidget(btn_reset_game_);
	AddWidget(btn_credits_);

}



void I_cSettingsWindow::OnResetGame(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_RESET_GAME, 0);
}



void I_cSettingsWindow::OnShowCredits(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SHOW_CREDITS, 0);
}



void I_cSettingsWindow::OnMusicOnOff(void *ptr_data)
{
 gGameData.music_on_ =! gGameData.music_on_;

 if (gGameData.music_on_)
     gSoundBlaster.PlayMainMenu();
		 else gSoundBlaster.MusicOff();

}



void I_cSettingsWindow::OnSfxOnOff(void *ptr_data)
{
	gGameData.sfx_on_ = !gGameData.sfx_on_;

	if (gGameData.sfx_on_)
		gSoundBlaster.PlayPop();
	else gSoundBlaster.SfxOff();
}

void I_cSettingsWindow::OnReturn(void* ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_MAIN_MENU;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);
}



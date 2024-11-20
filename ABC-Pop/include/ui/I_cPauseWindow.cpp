#include "I_cPauseWindow.h"
#include "include/I_cAssetmanager.h"


I_cPauseWindow::I_cPauseWindow()
{
}


I_cPauseWindow::~I_cPauseWindow()
{
}


void I_cPauseWindow::Draw()
{
 I_cWindow::Draw();
}


void I_cPauseWindow::Init(void)
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 25);


	btn_quit_current_game_ = new I_cImageButton();
	btn_resume_game_ = new I_cImageButton();

	SDL_Rect rc_resume = GAMEAPI_GetRect(bt_pos_x, bt_pos_y, bt_w, bt_h);
	SDL_Rect rc_quit = GAMEAPI_GetRect(bt_pos_x, bt_pos_y + bt_h*2, bt_w, bt_h);

	int icon_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
	int pic_x = rc_quit.w / 2;

	btn_quit_current_game_->SetPos(rc_quit.x, rc_quit.y, rc_quit.w, rc_quit.h);
	btn_quit_current_game_->SetText("Quit Current Game", GAMEAPI_GetColor(255, 255, 255));
	btn_quit_current_game_->SetUsingFonts(true);
	btn_quit_current_game_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_RED, true), gAssetManager->GetUIButton(BUTTON_COLOR_RED, false));
	btn_quit_current_game_->AddPicture(GAMEAPI_GetRect(pic_x, rc_quit.y + icon_size/2, icon_size, icon_size), gAssetManager->GetExit());
	btn_quit_current_game_->SetShowPic(true);
    btn_quit_current_game_->SetShowText(false);



	pic_x = rc_resume.w / 2;
	btn_resume_game_->SetPos(rc_resume.x, rc_resume.y, rc_resume.w, rc_resume.h);
	btn_resume_game_->SetText("Resume Game", GAMEAPI_GetColor(255, 255, 255));
	btn_resume_game_->SetUsingFonts(true);
	btn_resume_game_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
	btn_resume_game_->AddPicture(GAMEAPI_GetRect(pic_x, rc_resume.y + icon_size/2, icon_size, icon_size), gAssetManager->GetBackToGame());
	btn_resume_game_->SetShowPic(true);
    btn_resume_game_->SetShowText(false);




	AddWidget(btn_quit_current_game_);
	AddWidget(btn_resume_game_);

	btn_resume_game_->OnClick.bind(this, &I_cPauseWindow::OnResume);   // Resume Game from paused state
    btn_quit_current_game_->OnClick.bind(this, &I_cPauseWindow::QuitCurrentGame); // Quit current game from pause menu

	// za ovaj prozor netreba fade
	fadeActive_ = false;

}





void I_cPauseWindow::OnResume(void *prt_data)
{
 GAMEAPI_CallEvent(GAMEAPI_EVENT_RESUME_GAME,0);
}


void I_cPauseWindow::QuitCurrentGame(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_QUIT_CURRENT_GAME,0);
}



/*

void I_cPauseWindow::OnContinue(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_WORLD_COMPLETE_CONTINUE, NULL);
}
*/
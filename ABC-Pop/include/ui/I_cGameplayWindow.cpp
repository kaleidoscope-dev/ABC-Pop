#include "I_cGameplayWindow.h"
#include "include/I_cAssetmanager.h"


I_cGameplayWindow::I_cGameplayWindow()
{
}


I_cGameplayWindow::~I_cGameplayWindow()
{
}




void I_cGameplayWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_pause_game = new I_cButton(); // back to main menu

	btn_pause_game->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_pause_game->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_pause_game->OnClick.bind(this, &I_cGameplayWindow::OnPauseGame);  // back to main menu from credits window
	AddWidget(btn_pause_game);

}


void I_cGameplayWindow::Init(void)
{

	CreateBackButton();

	// za ovaj prozor netreba fade, inace dobijemo fade na pause
	fadeActive_ = false;

	//fadeOut_ = false;


}


void I_cGameplayWindow::Draw(void)
{
 I_cWindow::Draw();
}



void I_cGameplayWindow::OnPauseGame(void* ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_PAUSE_GAME, NULL);
}





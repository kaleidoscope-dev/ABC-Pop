#include "I_cWorldSelectWindow.h"
#include "../gameapi.h"
#include "../I_cAssetmanager.h"
#include "../I_cGameData.h"

I_cWorldSelectWindow::I_cWorldSelectWindow()
{
}


I_cWorldSelectWindow::~I_cWorldSelectWindow()
{
}


void I_cWorldSelectWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_return_ = new I_cButton(); // back to main menu

	btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_return_->OnClick.bind(this, &I_cWorldSelectWindow::OnReturn);  // back to main menu from credits window
}


void I_cWorldSelectWindow::Init(void)
{


	for (int c = 0; c < WORLD_COUNT; c++)
	{
		btn_world_select[c] = new I_cButton();
		AddWidget(btn_world_select[c]);
	}


	//AddWidget(pic_frame);

	GAMEAPI_WORLD_TYPE rnd_background = (GAMEAPI_WORLD_TYPE)rm->IRandom(0, 4);
	SetBackgroundTexture(gAssetManager->GetWorldBackground(rnd_background));

	CreateBackButton();


	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 18);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);


	btn_world_select[WORLD_FOREST]->SetPos(bt_pos_x,bt_pos_y  ,  bt_w,bt_h);
	btn_world_select[WORLD_WINTER]->SetPos(bt_pos_x, bt_pos_y + bt_h, bt_w, bt_h);
	btn_world_select[WORLD_DESERT]->SetPos(bt_pos_x, bt_pos_y + bt_h * 2, bt_w, bt_h);
	btn_world_select[WORLD_GRAVEYARD]->SetPos(bt_pos_x, bt_pos_y + bt_h * 3, bt_w, bt_h);
	btn_world_select[WORLD_CANDYLAND]->SetPos(bt_pos_x, bt_pos_y + bt_h * 4, bt_w, bt_h);


	btn_world_select[WORLD_FOREST]->SetTexture(gAssetManager->GetWorldSelectButton(WORLD_FOREST), gAssetManager->GetWorldSelectButton(WORLD_FOREST));
	btn_world_select[WORLD_WINTER]->SetTexture(gAssetManager->GetWorldSelectButton(WORLD_WINTER), gAssetManager->GetWorldSelectButton(WORLD_WINTER));
	btn_world_select[WORLD_DESERT]->SetTexture(gAssetManager->GetWorldSelectButton(WORLD_DESERT), gAssetManager->GetWorldSelectButton(WORLD_DESERT));
	btn_world_select[WORLD_GRAVEYARD]->SetTexture(gAssetManager->GetWorldSelectButton(WORLD_GRAVEYARD), gAssetManager->GetWorldSelectButton(WORLD_GRAVEYARD));
	btn_world_select[WORLD_CANDYLAND]->SetTexture(gAssetManager->GetWorldSelectButton(WORLD_CANDYLAND), gAssetManager->GetWorldSelectButton(WORLD_CANDYLAND));


	// select world
	
	for (int c = 0; c < WORLD_COUNT; c++)
	{
		GAMEAPI_EVENT_DATA *data = new GAMEAPI_EVENT_DATA;

		data->id = c;  // forest = 0 , winter = 1, ...
		btn_world_select[c]->SetUserData(data);
		btn_world_select[c]->OnClick.bind(this, &I_cWorldSelectWindow::OnClick);
	}

	AddWidget(btn_return_);
	ReinitPhase();
}






// ako svijet nije zavrsen, oboji tipku za taj svijet u crno bijelo i onesposobi tipku
// osim za prvi svijet. prvi svijet nikada nije onesposobljen
void I_cWorldSelectWindow::ReinitPhase(void) 
{

	for (int c = 0; c < WORLD_COUNT; c++)
	{
		if (gGameData.IsInProgress(c) == false && c > 0 && gGameData.IsWorldFinished(c) == false)
		{
			I_cButton *btn = (I_cButton*)GetControl(c);
			SDL_Texture *tex = btn->GetTexture();
			SDL_SetTextureColorMod(tex, 150, 150, 150);
			btn->SetEnable(false);
		}

		// NOTE: svijet koji je zavrsen nikada nesmije biti onesposoboljen
		if (gGameData.IsInProgress(c) == true)
		{
			I_cButton *btn = (I_cButton*)GetControl(c);
			SDL_Texture *tex = btn->GetTexture();
			SDL_SetTextureColorMod(tex, 255, 255, 255);
			btn->SetEnable(true);
		}
	}

}



void I_cWorldSelectWindow::OnClick(void *ptr_data)
{
 
	GAMEAPI_CallEvent(GAMEAPI_EVENT_WORLD_SELECT,ptr_data);
  
}



void I_cWorldSelectWindow::OnReturn(void* ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_MAIN_MENU;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);
}





void I_cWorldSelectWindow::Draw(void)
{


 I_cWindow::Draw();
}

#include "I_cCollectionsWindow.h"
#include "include/gameapi.h"
#include "include/I_cAssetmanager.h"

I_cCollectionsWindow::I_cCollectionsWindow()
{
}


I_cCollectionsWindow::~I_cCollectionsWindow()
{
/*
	delete btn_show_collections_;
	delete btn_dictionary_;
	delete btn_alphabet_;
	*/
}



void I_cCollectionsWindow::Draw(void)
{

	I_cWindow::Draw();

}

void I_cCollectionsWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_return_ = new I_cButton(); // back to main menu

	btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_return_->OnClick.bind(this, &I_cCollectionsWindow::OnReturn);  // back to main menu from credits window
}


void I_cCollectionsWindow::Init(void)
{
	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)rm->IRandom(0, 4)));

	btn_show_collections_ = new I_cImageButton("bt_collection");
	btn_dictionary_ = new I_cImageButton("bt_dict");
	//btn_credits_ = new I_cImageButton("bt_alpha");


	CreateBackButton();



	//btn_balloon_collection_ = (I_cButton*)gAnduin->CreateWidget(gui_wnd_collections_select, ANDUIN_CONTROL_BUTTON);
	//btn_dictionary_ = (I_cButton*)gAnduin->CreateWidget(gui_wnd_collections_select, ANDUIN_CONTROL_BUTTON);
	//btn_alphabet_ = (I_cButton*)gAnduin->CreateWidget(gui_wnd_collections_select, ANDUIN_CONTROL_BUTTON);

	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);


	SDL_Rect rc_collections_ = { bt_pos_x,bt_pos_y + bt_h ,  bt_w,bt_h };
	SDL_Rect rc_dict = { bt_pos_x,bt_pos_y + bt_h * 2, bt_w, bt_h };
	SDL_Rect rc_alpha = { bt_pos_x,bt_pos_y + bt_h * 3, bt_w, bt_h };
	SDL_Rect rc_credits = { bt_pos_x,bt_pos_y + bt_h * 4, bt_w, bt_h };




	// stvori balloons button
	btn_show_collections_->SetPos(rc_collections_.x, rc_collections_.y, rc_collections_.w, rc_collections_.h);
	btn_show_collections_->SetText("Animals", GAMEAPI_GetColor(255, 255, 255));
	btn_show_collections_->SetUsingFonts(true);
	btn_show_collections_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_BLUE,true), gAssetManager->GetUIButton(BUTTON_COLOR_BLUE, false));
	btn_show_collections_->OnClick.bind(this, &I_cCollectionsWindow::OnShow_AnimalCollections);    // Show Collections window


	int world = GAMEAPI_GetRandom(0, 4);
	int ani = GAMEAPI_GetRandom(0, 5);
	int ani_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

    /*
	int pic_x = rc_collections_.w / 2 - ani_size / 2;
	btn_show_collections_->AddPicture(GAMEAPI_GetRect(pic_x, rc_collections_.y + ani_size, ani_size, ani_size), gAssetManager->GetAnimal(world, ani));

	world = GAMEAPI_GetRandom(0, 4);
	ani = GAMEAPI_GetRandom(0, 5);

	pic_x = rc_collections_.w / 2;
	btn_show_collections_->AddPicture(GAMEAPI_GetRect(pic_x, rc_collections_.y, ani_size, ani_size), gAssetManager->GetAnimal(world, ani));

	world = GAMEAPI_GetRandom(0, 4);
	ani = GAMEAPI_GetRandom(0, 5);

	pic_x = rc_collections_.w / 2 + ani_size / 2;
	btn_show_collections_->AddPicture(GAMEAPI_GetRect(pic_x, rc_collections_.y + ani_size, ani_size, ani_size), gAssetManager->GetAnimal(world, ani));
    */
	int animal = GAMEAPI_GetRandom(0,5);
	//int ani_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

    // left
    int animal_x = GAMEAPI_GetPercentage(40,rc_collections_.w);
    int animal_y = GAMEAPI_GetPercentage(35,rc_collections_.h);
	btn_show_collections_->AddPicture(GAMEAPI_GetRect(rc_collections_.x + animal_x, rc_collections_.y + animal_y, ani_size, ani_size), gAssetManager->GetAnimal(world,animal));


	world = GAMEAPI_GetRandom(0, 4);
	animal = GAMEAPI_GetRandom(0, 5);

    // right
    animal_x = GAMEAPI_GetPercentage(50,rc_collections_.w);
    animal_y = GAMEAPI_GetPercentage(35,rc_collections_.h);
	btn_show_collections_->AddPicture(GAMEAPI_GetRect(rc_collections_.x + animal_x, rc_collections_.y + animal_y, ani_size, ani_size), gAssetManager->GetAnimal(world, animal));

	world = GAMEAPI_GetRandom(0, 4);
	animal = GAMEAPI_GetRandom(0, 5);

    // middle
    animal_x = GAMEAPI_GetPercentage(45,rc_collections_.w);
    animal_y = GAMEAPI_GetPercentage(10,rc_collections_.h);
	btn_show_collections_->AddPicture(GAMEAPI_GetRect(rc_collections_.x + animal_x, rc_collections_.y + animal_y , ani_size, ani_size), gAssetManager->GetAnimal(world, animal));


	btn_dictionary_->SetPos(rc_dict.x, rc_dict.y, rc_dict.w, rc_dict.h);
	btn_dictionary_->SetText("Dictionary", GAMEAPI_GetColor(255, 255, 255));
	btn_dictionary_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
	btn_dictionary_->SetUsingFonts(true);
	btn_dictionary_->OnClick.bind(this, &I_cCollectionsWindow::OnShow_Dictionary);    // Show Collections window

	if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
	{
		int dic_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 12);
		int pic_x = rc_dict.w / 2;
		btn_dictionary_->AddPicture(GAMEAPI_GetRect(pic_x, rc_dict.y + dic_size/3, dic_size, dic_size), gAssetManager->GetLetterMiss());

	}




	//btn_credits_->SetPos(rc_alpha.x, rc_alpha.y, rc_alpha.w, rc_alpha.h);
	//btn_credits_->SetText("Credits", GAMEAPI_GetColor(255, 255, 255));
	//btn_credits_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_YELLOW, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
	//btn_credits_->SetUsingFonts(true);
	//btn_credits_->OnClick.bind(this, &I_cCollectionsWindow::OnShow_Keyboard);    // Show Collections window

	AddWidget(btn_show_collections_);
	AddWidget(btn_dictionary_);
	AddWidget(btn_return_);

	ReinitPhase();
}





void I_cCollectionsWindow::ReinitPhase(void)
{

	if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
	{
		btn_show_collections_->SetShowPic(true);
		btn_show_collections_->SetShowText(false);

		btn_dictionary_->SetShowPic(true);
		btn_dictionary_->SetShowText(false);


	}else {
					btn_show_collections_->SetShowPic(false);
					btn_show_collections_->SetShowText(true);

					btn_dictionary_->SetShowPic(false);
					btn_dictionary_->SetShowText(true);

				}

}







void I_cCollectionsWindow::OnShow_AnimalCollections(void *ptr_data)
{
	GAMEAPI_EVENT_DATA *edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_ANIMAL_COLLECTION_SELECT;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);
}



void I_cCollectionsWindow::OnReturn(void* ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_MAIN_MENU;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);
}






void I_cCollectionsWindow::OnShow_Dictionary(void *ptr_data)
{
	GAMEAPI_EVENT_DATA *edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_DICTIONARY_SELECT;

	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);

}



void I_cCollectionsWindow::OnShow_Keyboard(void *ptr_data)
{
	GAMEAPI_EVENT_DATA *edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_KEYBOARD_SELECT;

	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);

}

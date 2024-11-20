#include "I_cMainWindow.h"
#include "include/I_cAssetmanager.h"


I_cMainWindow::I_cMainWindow()
{
}


I_cMainWindow::~I_cMainWindow()
{
}


void I_cMainWindow::Draw()
{


 I_cWindow::Draw();


}



void I_cMainWindow::Init(void)
{

	btn_start_game_ = new I_cImageButton();
	btn_show_collections_ = new I_cImageButton();
	btn_options_ = new I_cImageButton();
#ifndef __ANDROID__
	btn_quit_game_ = new I_cImageButton();
#endif


	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W,90);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H,15);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);

	SDL_Rect rc_image =        { bt_pos_x,bt_pos_y + bt_h * 4  ,  bt_w,bt_h };
	SDL_Rect rc_start =        { bt_pos_x,bt_pos_y  ,  bt_w,bt_h};
	SDL_Rect rc_collections_ = { bt_pos_x,bt_pos_y + bt_h, bt_w, bt_h };
	SDL_Rect rc_options =      { bt_pos_x,bt_pos_y + bt_h*2, bt_w, bt_h };
	SDL_Rect rc_quit =         { bt_pos_x,bt_pos_y + bt_h*3, bt_w, bt_h };

	int bln_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);


	btn_start_game_->SetPos(rc_start.x, rc_start.y, rc_start.w, rc_start.h);
	btn_start_game_->SetText("Start Game", GAMEAPI_GetColor(255, 255, 255));
	btn_start_game_->SetUsingFonts(true);
	btn_start_game_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));

    
	// LEFT
    int balloon_x = GAMEAPI_GetPercentage(40,rc_start.w);
    int balloon_y = GAMEAPI_GetPercentage(35,rc_start.h);
	btn_start_game_->AddPicture(GAMEAPI_GetRect(rc_start.x + balloon_x, rc_start.y + balloon_y, bln_size, bln_size),gAssetManager->GetBalloon((GAMEAPI_BALLOON_COLOR)GAMEAPI_GetRandom(1,7)));

	// RIGHT
    balloon_x = GAMEAPI_GetPercentage(50,rc_start.w);
    balloon_y = GAMEAPI_GetPercentage(35,rc_start.h);
	btn_start_game_->AddPicture(GAMEAPI_GetRect(rc_start.x + balloon_x, rc_start.y + balloon_y, bln_size, bln_size), gAssetManager->GetBalloon(GAMEAPI_BALLOON_COLOR_YELLOW));

	// MIDDLE
    balloon_x = GAMEAPI_GetPercentage(45,rc_start.w);
    balloon_y = GAMEAPI_GetPercentage(10,rc_start.h);
	btn_start_game_->AddPicture(GAMEAPI_GetRect(rc_start.x + balloon_x, rc_start.y + balloon_y, bln_size, bln_size), gAssetManager->GetBalloon(GAMEAPI_BALLOON_COLOR_RED));


	btn_show_collections_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_BLUE, true), gAssetManager->GetUIButton(BUTTON_COLOR_BLUE, false));
#ifndef __ANDROID__
	btn_quit_game_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_RED, true), gAssetManager->GetUIButton(BUTTON_COLOR_RED, false));
#endif

	btn_options_->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_YELLOW, true), gAssetManager->GetUIButton(BUTTON_COLOR_YELLOW, false));


	btn_options_->SetPos(rc_options.x, rc_options.y, rc_options.w, rc_options.h);
	btn_options_->SetText("Options", GAMEAPI_GetColor(0, 120, 0));
	btn_options_->SetUsingFonts(true);
	int sett_size_w = GAMEAPI_GetPercentage(rc_options.w, 20);
	int sett_size_h = GAMEAPI_GetPercentage(rc_options.h, 50);
	int options_x = GAMEAPI_GetPercentage(50,rc_options.w);
	int options_y = GAMEAPI_GetPercentage(50,rc_options.h);
	btn_options_->AddPicture(GAMEAPI_GetRect(rc_options.x + options_x - sett_size_w/2, rc_options.y + options_y - sett_size_h/2, sett_size_w, sett_size_h), gAssetManager->GetGears());

#ifndef __ANDROID__
	int exit_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	btn_quit_game_->SetPos(rc_quit.x, rc_quit.y, rc_quit.w, rc_quit.h);
	btn_quit_game_->SetText("Quit Game", GAMEAPI_GetColor(0, 0, 0));
	btn_quit_game_->SetUsingFonts(true);
	int pic_x = rc_quit.w / 2;
	btn_quit_game_->AddPicture(GAMEAPI_GetRect(pic_x, rc_quit.y + 15, exit_size, exit_size), gAssetManager->GetExit());
#endif

	//btn_show_credits_->SetText("   Credits   ", GAMEAPI_GetColor(255, 255, 255));
	//btn_show_credits_->SetPos(rc_credits.x, rc_credits.y, rc_credits.w, rc_credits.h);
	//btn_show_credits_->SetUsingFonts(true);
	
	btn_show_collections_->SetPos(rc_collections_.x, rc_collections_.y, rc_collections_.w, rc_collections_.h);
	btn_show_collections_->SetText("Collections", GAMEAPI_GetColor(255, 255, 255));
	btn_show_collections_->SetUsingFonts(true);



	int world = GAMEAPI_GetRandom(0,4);
	int animal = GAMEAPI_GetRandom(0,5);
	int ani_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

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

	// main menu ce uvijek imati random pozadinu prilikom starta
	GAMEAPI_WORLD_TYPE rnd_background = (GAMEAPI_WORLD_TYPE)rm->IRandom(0, 4);
	SetBackgroundTexture(gAssetManager->GetWorldBackground(rnd_background));


#ifndef __ANDROID__
	btn_quit_game_->OnClick.bind(this, &I_cMainWindow::OnQuit);        //  Quit Gane
#endif

	btn_show_collections_->OnClick.bind(this, &I_cMainWindow::OnCollections);    // Show Collections window
	btn_start_game_->OnClick.bind(this, &I_cMainWindow::OnStartGame);   //  Show World Select Menu
	btn_options_->OnClick.bind(this, &I_cMainWindow::OnOptions); // Reset game iz main menu


	AddWidget(btn_start_game_);
	AddWidget(btn_show_collections_);
	AddWidget(btn_options_);
#ifndef __ANDROID__
	AddWidget(btn_quit_game_);
#endif


	ReinitPhase();



}


void I_cMainWindow::ReinitPhase(void)
{

	if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
	{
		btn_start_game_->SetShowPic(true);
		btn_start_game_->SetShowText(false);

		btn_show_collections_->SetShowPic(true);
		btn_show_collections_->SetShowText(false);

		btn_options_->SetShowPic(true);
		btn_options_->SetShowText(false);
#ifndef __ANDROID__
		btn_quit_game_->SetShowPic(true);
		btn_quit_game_->SetShowText(false);
#endif

	}else {
				 btn_start_game_->SetShowPic(false);
				 btn_start_game_->SetShowText(true);

				 btn_options_->SetShowPic(false);
				 btn_options_->SetShowText(true);

#ifndef __ANDROID__
				 btn_quit_game_->SetShowPic(false);
				 btn_quit_game_->SetShowText(true);
#endif


				 btn_show_collections_->SetShowPic(false);
				 btn_show_collections_->SetShowText(true);
	      }

}



void I_cMainWindow::OnCollections(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SHOW_COLLECTION, 0);
}

void I_cMainWindow::OnQuit(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_QUIT_GAME, 0);

}

void I_cMainWindow::OnStartGame(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_START_GAME, 0);
}

void I_cMainWindow::OnOptions(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SHOW_OPTIONS, 0);
}

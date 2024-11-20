#include "I_cUIMain.h"
#include "anduin/I_cAndUIn.h"
#include "I_cAssetmanager.h"
#include "I_cGameData.h"

I_cUIMain::I_cUIMain()
{
}


I_cUIMain::~I_cUIMain()
{

}


void I_cUIMain::DeinitAll(void)
{
	delete gui_wnd_world_select;
	delete wnd_running;
	delete gui_wnd_phase_over;
	delete gui_wnd_settings;
	delete gui_wnd_main_menu;
	delete gui_wnd_paused;
	delete gui_wnd_animal_collections;
	delete gui_wnd_collections_select;
	delete wnd_credits;
	delete gui_wnd_dictionary;
	delete gui_wnd_world_complete;
    delete gui_wnd_winner;
    delete gui_wnd_reset_message;



	delete gui_wnd_forest_level_select;
	delete gui_wnd_winter_level_select;
	delete gui_wnd_desert_level_select;
	delete gui_wnd_graveyard_level_select;
	delete gui_wnd_candyland_level_select;

	delete gui_wnd_level_complete;

	//delete gui_wnd_game_over;
	delete gAnduin;
}


// main menu
void I_cUIMain::CreateMainMenu(void)
{
	// forest level selct
	gui_wnd_main_menu = new I_cMainWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_main_menu);

	gui_wnd_main_menu->Init();

}


// Reiniciraj podatke. Zovemo iz Engine::ReinitPhase
void I_cUIMain::ReinitPhase(void)
{
 gui_wnd_main_menu->ReinitPhase();
 gui_wnd_collections_select->ReinitPhase();
 gui_wnd_world_select->ReinitPhase();

 //gui_wnd_forest_level_select->ReinitPhase();
 //gui_wnd_winter_level_select->ReinitPhase();
 //gui_wnd_desert_level_select->ReinitPhase();
 //gui_wnd_graveyard_level_select->ReinitPhase();
 //gui_wnd_candyland_level_select->ReinitPhase();
}


// Stvori world select window. 
I_cWorldSelectWindow *I_cUIMain::CreateWorldSelectWindow(void)
{
	int y = 80;
	I_cWorldSelectWindow *wnd = new I_cWorldSelectWindow();
	gAnduin->CreateAnduinWindow(wnd);

	wnd->Init();

	return wnd;
}




// stvori sve levele
I_cLevelSelectWindow *I_cUIMain::CreateLevels(GAMEAPI_WORLD_TYPE type)
{
	// forest level selct
	I_cLevelSelectWindow *wnd = new I_cLevelSelectWindow();
	gAnduin->CreateAnduinWindow(wnd);
	

	// stvori LEVEL_COUNT buttona na prozoru. svi buttoni su nevidljivi na pocetku
	for (int c = 0, x = 0, y = 0; c < GAMEAPI_LEVEL_COUNT; c++, x++)
	{
	 I_cButton *btn = (I_cButton*)gAnduin->CreateWidget(wnd, ANDUIN_CONTROL_BUTTON);
	 GAMEAPI_EVENT_DATA *data = new GAMEAPI_EVENT_DATA;
	 data->id = c;
	 btn->SetUserData(data);
	 btn->SetTexture(gAssetManager->GetLevelSelectButtonTexture(type), gAssetManager->GetLevelSelectButtonTexture(type));

	 if (gGameData.IsLevelFinished(type,c))
	     btn->SetVisible(true);
			 else btn->SetVisible(false);
	}

	// postavi poziciju tipki na rijeku i stazu
	// 1
	int pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 19);
	int pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 18);
	int size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	int size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	wnd->GetControl(0)->SetPos(pos_x, pos_y, size_w, size_h);

	// 2
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 70);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	wnd->GetControl(1)->SetPos(pos_x, pos_y, size_w, size_h);

	// 3
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 50);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	wnd->GetControl(2)->SetPos(pos_x, pos_y, size_w, size_h);

	// 4
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 62);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	wnd->GetControl(3)->SetPos(pos_x, pos_y, size_w, size_h);

	// 5
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 75);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 70);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	wnd->GetControl(4)->SetPos(pos_x, pos_y, size_w, size_h);

	// 6
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 87);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	wnd->GetControl(5)->SetPos(pos_x, pos_y, size_w, size_h);

	// stvori marker button, i postavi na level 1
	I_cMarkerButton *btn_level_marker = new I_cMarkerButton();
	SDL_Rect rc = wnd->GetControl(0)->widget_rect_;



	btn_level_marker->SetPos(rc.x,rc.y, rc.w, rc.h);
	btn_level_marker->SetTexture(gAssetManager->GetLevelMarkerTexture(type), gAssetManager->GetLevelMarkerTexture(type));
	btn_level_marker->SetText("1", GAMEAPI_GetColor(255, 255, 255));
	btn_level_marker->SetUsingFonts(true);
	wnd->AddWidget(btn_level_marker);



    // i na kraju, postavi samo prvi nivo button da je vidljiv
	I_cButton *ptr_level1 = (I_cButton*)wnd->GetControl(0);
	ptr_level1->SetVisible(true);



 return wnd;
}


// credits
void I_cUIMain::CreateCreditsWindow(void)
{
 wnd_credits = new I_cCreditsWindow();
 gAnduin->CreateAnduinWindow(wnd_credits);

 wnd_credits->Init();


}






// level complete
void I_cUIMain::CreateLevelCompleteWindow(void)
{
	// stvori level complete prozor
	gui_wnd_level_complete = new I_cLevelCompleteWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_level_complete);
	gui_wnd_level_complete->Init();

}

void I_cUIMain::CreatePhaseOverWindow(void)
{
	// stvori game over continue screen
   gui_wnd_phase_over = new I_cPhaseOverWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_phase_over);
   gui_wnd_phase_over->Init();

}


//  World Complete Window
void I_cUIMain::CreateWorldCompleteWindow(void)
{
	// stvori world complete window i button
	gui_wnd_world_complete = new I_cWorldCompleteWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_world_complete);
	gui_wnd_world_complete->Init();

}




// paused menu
void I_cUIMain::CreatePauseWindow(void)
{
	gui_wnd_paused = new I_cPauseWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_paused);
	gui_wnd_paused->Init();

}



// stvori window s ballons, dict i alpabet
void I_cUIMain::CreateCollectionSelectWindow(void)
{
	gui_wnd_collections_select = new I_cCollectionsWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_collections_select);

	gui_wnd_collections_select->Init();
	//gui_wnd_collections_select->AddWidget(btn_back_to_main_menu_);

}


// Animal collection window
void I_cUIMain::CreateAnimalCollectionWindow(void)
{

	gui_wnd_animal_collections = new I_cAnimalCollectionWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_animal_collections);

	//gui_wnd_animal_collections->SetBackgroundTexture(gAssetManager->GetWorldBackground());
	gui_wnd_animal_collections->Init(gAnduin);
	//gui_wnd_animal_collections->AddWidget(btn_back_to_collections_); // povratak iz world select

}


void I_cUIMain::CreateSettingsWindow(void)
{
 gui_wnd_settings = new I_cSettingsWindow();
 gAnduin->CreateAnduinWindow(gui_wnd_settings);

 //gui_wnd_animal_collections->SetBackgroundTexture(gAssetManager->GetWorldBackground());
 gui_wnd_settings->Init();
 //gui_wnd_settings->AddWidget(btn_back_to_main_menu_); // povratak iz world select

}


void I_cUIMain::CreateResetMessageWindow(void)
{
   gui_wnd_reset_message = new I_cResetMessageWindow();
   gAnduin->CreateAnduinWindow(gui_wnd_reset_message);

   //gui_wnd_animal_collections->SetBackgroundTexture(gAssetManager->GetWorldBackground());
   gui_wnd_reset_message->Init();
   //gui_wnd_settings->AddWidget(btn_back_to_main_menu_); // povratak iz world select
}


void I_cUIMain::CreateWinnerWindow(void)
{
 gui_wnd_winner = new I_cWinnerWindow();
 gAnduin->CreateAnduinWindow(gui_wnd_winner);
 gui_wnd_winner->Init();
}




// DEPRECATED
void I_cUIMain::CreateKeyboardWindow(void)
{
/*
	gui_wnd_keyboard = new I_cKeyboardWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_keyboard);

	gui_wnd_keyboard->SetBackgroundTexture(gAssetManager->GetWorldBackground(WORLD_FOREST));

	gui_wnd_keyboard->AddWidget(btn_back_to_collections_); // povratak iz world select

	
	gui_wnd_keyboard->Init(gAnduin);
	*/
}



// Create Dict. Window
void I_cUIMain::CreateDictionaryWindow(void)
{
	gui_wnd_dictionary = new I_cDictionaryWindow();
	gAnduin->CreateAnduinWindow(gui_wnd_dictionary);

	gui_wnd_dictionary->SetBackgroundTexture(gAssetManager->GetWorldBackground(WORLD_FOREST));


	gui_wnd_dictionary->Init();
	//gui_wnd_dictionary->AddWidget(btn_back_to_collections_); // povratak iz world select
}




void I_cUIMain::AnduinInit(void)
{




	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	gAnduin = new I_cAndUIn();
	
	// Main menu, Pause i world select
	CreateMainMenu();
	CreatePauseWindow();
	gui_wnd_world_select = CreateWorldSelectWindow();
 

   
	// wnd_running za pause button - preimenovati u HUD - dodati zvjedice, text traku itd.
     wnd_running = new I_cGameplayWindow(); 
	 gAnduin->CreateAnduinWindow(wnd_running);
     wnd_running->Init();




    // stvori credits window 
    CreateCreditsWindow();	
    CreateCollectionSelectWindow();
	CreateAnimalCollectionWindow();
	CreateDictionaryWindow();
	CreateSettingsWindow();
    CreateResetMessageWindow();
    CreateWinnerWindow();

		gui_wnd_forest_level_select = CreateLevelWindow(WORLD_FOREST);
		gui_wnd_winter_level_select = CreateLevelWindow(WORLD_WINTER);
		gui_wnd_desert_level_select = CreateLevelWindow(WORLD_DESERT);
		gui_wnd_graveyard_level_select = CreateLevelWindow(WORLD_GRAVEYARD);
		gui_wnd_candyland_level_select = CreateLevelWindow(WORLD_CANDYLAND);

	CreateLevelCompleteWindow();
	CreatePhaseOverWindow();


 CreateWorldCompleteWindow();



	// Sve je gotovo. Prvi menu koji pokazujemo je main menu
    gAnduin->SetActiveWindow(gui_wnd_main_menu);
	current_ui_state_ = GAMEAPI_UI_MAIN_MENU;

}


I_cLevelSelectWindow *I_cUIMain::CreateLevelWindow(GAMEAPI_WORLD_TYPE type)
{

	I_cLevelSelectWindow *level_window = new I_cLevelSelectWindow();
	gAnduin->CreateAnduinWindow(level_window);


	level_window->Init(type);

	return level_window;

	return NULL;
}




I_cLevelSelectWindow *I_cUIMain::GetLevelSelectWindow(GAMEAPI_WORLD_TYPE type)
{

 switch(type)
       {
	    case WORLD_FOREST:
		 return gui_wnd_forest_level_select;
	    case WORLD_WINTER:
		 return gui_wnd_winter_level_select;
		case WORLD_DESERT:
		 return gui_wnd_desert_level_select;
		case WORLD_GRAVEYARD:
		 return gui_wnd_graveyard_level_select;
		case WORLD_CANDYLAND:
		 return gui_wnd_candyland_level_select;
       }

 return NULL;
}






void I_cUIMain::SetMenuState(GAMEAPI_UI_STATE state)
{
	current_ui_state_ = state;

	switch (current_ui_state_)
	       {
		    case GAMEAPI_UI_MAIN_MENU:
			 gAnduin->SetActiveWindow(gui_wnd_main_menu);
			 break;
			case GAMEAPI_UI_PAUSED:
			 gAnduin->SetActiveWindow(gui_wnd_paused);
			 break;

			case GAMEAPI_UI_IDLE:   // igra radi
			 gAnduin->SetActiveWindow(wnd_running);
			 break;

			case GAMEAPI_UI_CREDITS:
			 gAnduin->SetActiveWindow(wnd_credits);
			 break;

			case GAMEAPI_UI_WORLD_SELECT:
			 gAnduin->SetActiveWindow(gui_wnd_world_select);
			 break;

		    case GAMEAPI_UI_FOREST_LEVEL_SELECT:
			 gAnduin->SetActiveWindow(gui_wnd_forest_level_select);
			 break;

			case GAMEAPI_UI_WINTER_LEVEL_SELECT:
			 gAnduin->SetActiveWindow(gui_wnd_winter_level_select);
			 break;



			case GAMEAPI_UI_DESERT_LEVEL_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_desert_level_select);
				break;

			case GAMEAPI_UI_GRAVEYARD_LEVEL_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_graveyard_level_select);
				break;

			case GAMEAPI_UI_CANDYLAND_LEVEL_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_candyland_level_select);
				break;

			case GAMEAPI_UI_LEVEL_COMPLETE:
				gAnduin->SetActiveWindow(gui_wnd_level_complete);
				break;

				
			case GAMEAPI_UI_WORLD_COMPLETE:
				gAnduin->SetActiveWindow(gui_wnd_world_complete);
				break;


			case GAMEAPI_UI_PHASE_OVER:
                if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
                   {
				    gAnduin->SetActiveWindow(gui_wnd_phase_over);
                   }else {
                          gAnduin->SetActiveWindow(gui_wnd_winner);
                         }
				break;

      case GAMEAPI_UI_COLLECTIONS_SELECT:
			 gAnduin->SetActiveWindow(gui_wnd_collections_select);
			 break;

			case GAMEAPI_UI_ANIMAL_COLLECTION_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_animal_collections);
				break;


			case GAMEAPI_UI_DICTIONARY_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_dictionary);
				break;


			case GAMEAPI_UI_KEYBOARD_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_keyboard);
				break;

			case GAMEAPI_UI_SETTINGS_SELECT:
				gAnduin->SetActiveWindow(gui_wnd_settings);
				break;

         case GAMEAPI_UI_RESET_SELECT:
            gAnduin->SetActiveWindow(gui_wnd_reset_message);
            break;

            


			default:
			 gAnduin->SetActiveWindow(wnd_dummy);
			 break;
		   }
}



void I_cUIMain::Draw(void)
{
 switch(current_ui_state_)
       {
	    case GAMEAPI_UI_MAIN_MENU:
			gui_wnd_main_menu->Draw();

			 break;

		case GAMEAPI_UI_PAUSED:
			
			gui_wnd_paused->Draw();
			break;

		// TODO: samo texturu pokazati
		case GAMEAPI_UI_CREDITS:
			//panel_story_.Draw();
			wnd_credits->Draw();
			break;

    case GAMEAPI_UI_IDLE:
		   	 wnd_running->Draw();
		     break;

		case GAMEAPI_UI_FOREST_LEVEL_SELECT:
			gui_wnd_forest_level_select->Draw();
			break;

		case GAMEAPI_UI_WINTER_LEVEL_SELECT:
			gui_wnd_winter_level_select->Draw();
			break;

		case GAMEAPI_UI_DESERT_LEVEL_SELECT:
			gui_wnd_desert_level_select->Draw();
			break;

		case GAMEAPI_UI_GRAVEYARD_LEVEL_SELECT:
			gui_wnd_graveyard_level_select->Draw();
			break;

		case GAMEAPI_UI_CANDYLAND_LEVEL_SELECT:
			gui_wnd_candyland_level_select->Draw();
			break;


		case GAMEAPI_UI_WORLD_SELECT:
			gui_wnd_world_select->Draw();
			//wnd_forest_level_select->Draw();
			break;

		case GAMEAPI_UI_LEVEL_COMPLETE:
			gui_wnd_level_complete->Draw();
			break;

		// svijet zavrsen
		case GAMEAPI_UI_WORLD_COMPLETE:
		     gui_wnd_world_complete->Draw();
			 break;

		case GAMEAPI_UI_GAME_OVER:
			//gui_wnd_game_over->Draw();
			break;

		case GAMEAPI_UI_PHASE_OVER:
             if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
                 gui_wnd_phase_over->Draw();
                else gui_wnd_winner->Draw();
		   break;


		case GAMEAPI_UI_COLLECTIONS_SELECT:
			gui_wnd_collections_select->Draw();
			break;

		case GAMEAPI_UI_ANIMAL_COLLECTION_SELECT:
			gui_wnd_animal_collections->Draw();
			break;

			case GAMEAPI_UI_DICTIONARY_SELECT:
				gui_wnd_dictionary->Draw();
				break;

			case GAMEAPI_UI_KEYBOARD_SELECT:
				gui_wnd_keyboard->Draw();
				break;


			case GAMEAPI_UI_SETTINGS_SELECT:
				gui_wnd_settings->Draw();
				break;


         case GAMEAPI_UI_RESET_SELECT:
            gui_wnd_reset_message->Draw();
            break;




		default: break;
	   }
}

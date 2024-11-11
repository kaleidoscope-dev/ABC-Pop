#pragma once
#include "gameapi.h"
#include "anduin/I_cAndUIn.h"

#include "ui/I_cLevelSelectWindow.h"
#include "ui/I_cCreditsWindow.h"
#include "ui/I_cLevelCompleteWindow.h"
#include "ui/I_cWorldSelectWindow.h"
#include "ui/I_cCollectionsWindow.h"
#include "ui/I_cBalloonCollectionWindow.h"
#include "ui/I_cAnimalCollectionWindow.h"
#include "ui/I_cDictionaryWindow.h"
#include "ui/I_cKeyboardWindow.h"
#include "ui/I_cWorldCompleteWindow.h"
#include "ui/I_cPauseWindow.h"
#include "ui/I_cMainWindow.h"
#include "ui/I_cMarkerButton.h"
#include "ui/I_cPhaseOverWindow.h"
#include "ui/I_cSettingsWindow.h"
#include "ui/I_cGameplayWindow.h"
#include "ui/I_cResetMessageWindow.h"
#include "ui/I_cWinnerWindow.h"

class I_cUIMain
{
	public:
		I_cUIMain();
	   ~I_cUIMain();


	   void DeinitAll(void);
	   void AnduinInit(void);
	   void SetMenuState(GAMEAPI_UI_STATE state);
	   //void SetActiveWindow(
	   void Draw(void);
	   void Draw(GAMEAPI_UI_PANEL_TYPE type);

		 void ReinitPhase(void);

	   GAMEAPI_UI_PANEL_TYPE GetSelectedPanel(void);

	   //I_cAndUIn *anduin;

	   // main menu
		 I_cMainWindow *gui_wnd_main_menu;
	   I_cButton *btn_reset_game_;
	   I_cButton *btn_show_credits_;

	   // paused menu
	   I_cPauseWindow *gui_wnd_paused;
	   I_cButton *btn_pause_game;
	   //I_cButton *btn_back_to_main_menu_;


	   // world select menu
	   I_cWorldSelectWindow *gui_wnd_world_select;
	   //I_cWindow *gui_wnd_world_select;
	   //I_cButton *btn_world_select[WORLD_COUNT];
	   //I_cButton *btn_back_to_world_select_;

	   // level complete
	   I_cLevelCompleteWindow *gui_wnd_level_complete;
	   I_cButton *btn_continue_;

	   // world complete
	   I_cWorldCompleteWindow *gui_wnd_world_complete;
	   I_cButton *btn_world_complete_continue_;


	   // game over
      I_cPhaseOverWindow *gui_wnd_phase_over;
      I_cWinnerWindow *gui_wnd_winner;

      I_cResetMessageWindow *gui_wnd_reset_message;

	   // game finished
	   //I_cWindow *gui_wnd_game_finished;
	   //I_cButton *btn_game_finished_continue_;

		 // collection
		 I_cCollectionsWindow *gui_wnd_collections_select;

		 // balloon collection
		 I_cAnimalCollectionWindow *gui_wnd_animal_collections;
		 //I_cButton *btn_back_to_collections_;
		 
		 I_cSettingsWindow *gui_wnd_settings;


		 I_cDictionaryWindow *gui_wnd_dictionary;

		 I_cKeyboardWindow *gui_wnd_keyboard;

	   I_cButton *btn_levels[10];


	   I_cGameplayWindow *wnd_running;
	   I_cWindow *wnd_dummy;
	   I_cCreditsWindow *wnd_credits;

	   I_cLevelSelectWindow *gui_wnd_forest_level_select;
	   I_cLevelSelectWindow *gui_wnd_winter_level_select;
	   I_cLevelSelectWindow *gui_wnd_desert_level_select;
	   I_cLevelSelectWindow *gui_wnd_graveyard_level_select;
	   I_cLevelSelectWindow *gui_wnd_candyland_level_select;


	   I_cLevelSelectWindow *GetLevelSelectWindow(GAMEAPI_WORLD_TYPE type);


	   GAMEAPI_WORLD_TYPE selected_world_type_;
	   uint8_t selected_level_;

		 GAMEAPI_UI_STATE current_ui_state_;

		 void CreateWorldCompleteWindow(void);


	private:

			void CreateMainMenu(void);
			void CreatePauseWindow(void);
			I_cWorldSelectWindow *CreateWorldSelectWindow(void);
			I_cLevelSelectWindow *CreateLevels(GAMEAPI_WORLD_TYPE type);
			void CreateCollectionSelectWindow(void);
			void CreateCreditsWindow(void);
			void CreateLevelCompleteWindow(void);
			void CreateAnimalCollectionWindow(void);
			void CreateDictionaryWindow(void);
			void CreateKeyboardWindow(void);
			void CreatePhaseOverWindow(void);
			void CreateSettingsWindow(void);
            void CreateResetMessageWindow(void);
            void CreateWinnerWindow(void);

			I_cLevelSelectWindow *CreateLevelWindow(GAMEAPI_WORLD_TYPE type);

			//test

			void OnBackToCollections(void *ptr_data);





};
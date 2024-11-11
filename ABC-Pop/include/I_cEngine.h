#pragma once
#include "include/Framerate.h"
#include "include/I_cSoundBlaster.h"
#include "include/I_cUIMain.h"
#include "include/I_cBalloon.h"
#include "include/I_cLetter.h"
#include "include/I_cLevel.h"




class I_cEngine
{
 public:
		I_cEngine();
	   ~I_cEngine();
	   
        int Init(void);	   
	    
	  GAMEAPI_ERROR InitSDL(int w, int h, bool fs);
		GAMEAPI_ERROR InitAssets(void);
		bool IsRunning();
		//int Run(void);
	  void Render(void);
		void Stop(void);
		void SetGameState(GAMEAPI_GAMESTATE state);
		GAMEAPI_GAMESTATE GetGameState(void);
		void SetMenuState(GAMEAPI_UI_STATE state);
		void HandleEvents(GAMEAPI_EVENT_TYPE type, void *ptr_data);
		void SetUpdate(bool update);
		bool GetUpdate(void);
		void ReinitPhase(void);



 public:	   
       SDL_Surface *outputSurface_;	  
       SDL_Window *window_;
	   SDL_Renderer *renderer_;
	   Framerate framerate;
	   GAMEAPI_GAMESTATE gameState_;
	   int mouse_x_, mouse_y_;

	   I_cUIMain uiMain_;

 private:
		 void RenderUI(void);


		 static Uint32 OnTimer_AddBalloon(Uint32 interval, void *param);
		 static Uint32 OnTimer_GameTimer(Uint32 interval, void *param);

		 void HandleEvents_GameStateRunning(GAMEAPI_EVENT_TYPE type, void *ptr_data);
		 void HandleEvents_GameStateUI(GAMEAPI_EVENT_TYPE type, void *ptr_data);
		 void HandleEvents_GameStateShop(GAMEAPI_EVENT &event);
		 void HandleEvents_WalkOfShame(GAMEAPI_EVENT_TYPE type);
		 
		 void KillTimers(void);
		 void StartTimers(void);
		 void ResetGame(void);
         //void SetHandleEvents(bool b)

		 void RenderIntro(void);
		 //void RenderScoreLine(void);
	     uint8_t level_back;  // level background image

 private:
         bool run_;   
         SDL_Event sdlEvent_; 
		 bool showOverlay_;
		 //I_cTextTenderer textRenderer;


		 SDL_TimerID critter_timer_id_;
	     SDL_TimerID game_timer_id_; 
         bool handle_events_;

		 //I_cUITextPanel menuback_panel_;



		 SDL_Color back_color_;
		 GAMEAPI_BALLOON_COLOR sel_balloon_color_;
		 I_cBalloon *current_sel_ballon_;

		 //vector<I_cBalloon*>vBalloonDestroList;


		 I_cLevel *current_level_;
		 bool update_;

		 I_cLevel level_forest_[GAMEAPI_LEVEL_COUNT];
		 I_cLevel level_winter_[GAMEAPI_LEVEL_COUNT];
		 I_cLevel level_desert_[GAMEAPI_LEVEL_COUNT];
		 I_cLevel level_graveyard_[GAMEAPI_LEVEL_COUNT];
		 I_cLevel level_candyland_[GAMEAPI_LEVEL_COUNT];

		 void InitLevels(void);

		 void OnCredits(void);

		 void OnStartGame(void);
		 void OnCollections(void);
		 void OnQuit(void);
		 void OnOptions(void);

       void OnResetGame(void);
		 void OnStartLevel(void *ptr_data);

		 void OnBalloonCollections(void *ptr_data);


		 void wip_BindLevels(void);


		 void OnNextLevel(void *ptr_data);

		 void OnResume(void *ptr_data);
		 void OnPauseGame(void *ptr_data);
		 void QuitCurrentGame(void *ptr_data);
		 void OnBackToCollections(void *ptr_data);
		 


		 void OnWorldSelect(void *ptr_data);
		 void OnWorldComplete(void *ptr_data);    
		 void OnBack_FromLevelSelect(void *ptr_data);

		 void onClick_EmptyFunc_tmp(void *ptr_data); // // HACK to disable level repeat 


};
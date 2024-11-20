#include "I_cEngine.h"
#include "I_cAssetmanager.h"
#include <SDL.h>
#include <time.h>
#include <SDL_mixer.h>
#include <Box2D/Box2D.h>
#include "I_cText.h"
#include <SDL_image.h>
#include <include\I_cLog.h>
#include "I_cColorConversion.h"
#include "I_cGameData.h"

#include "anduin/anduin.h"



int GAMEAPI_WINDOW_W = 680;
int GAMEAPI_WINDOW_H = 1028;

// 
int GAMEAPI_COLLECTABLE_CHANCE = 10;



I_cParallax paralax;


I_cText txt_score;
I_cText txt_hs;
I_cText txt_pop_count;
I_cText txt_info;
I_cText txt_version;


I_cSoundBlaster gSoundBlaster;

Uint32 delay = 750;

uint32_t GAMEAPI_Pop_Count = 0;
uint32_t GAMEAPI_score = 0;

bool GAMEAPI_Loser = false;
bool GAMEAPI_Winner = false;


b2World *GAMEAPI_world_up = NULL;
b2World *GAMEAPI_world_down = NULL;


uint32_t GAMEAPI_HighScore = 0;





I_cEngine::I_cEngine() 
{
 outputSurface_ = NULL; 
 gameState_ = GAMESTATE_RUNNING;
 run_ = true;
 level_back = 0;

}



I_cEngine::~I_cEngine()
{
 gSoundBlaster.StopAll();
 delete GAMEAPI_world_up;
 delete GAMEAPI_world_down;
 uiMain_.DeinitAll();
 delete gLog;
 delete rm;
 delete gAssetManager;

 IMG_Quit();
 TTF_Quit();
 Mix_Quit();
 SDL_Quit();
}



void I_cEngine::KillTimers(void)
{
	SDL_RemoveTimer(critter_timer_id_);
	SDL_RemoveTimer(game_timer_id_);
}


void I_cEngine::StartTimers(void)
{
	critter_timer_id_ = SDL_AddTimer(delay, OnTimer_AddBalloon, this);
	game_timer_id_ = SDL_AddTimer(1000, OnTimer_GameTimer, 0);

	
}




int I_cEngine::Init(void)
{
	 int err = 0;
	 err = IMG_Init(IMG_INIT_PNG);
     string strerr = IMG_GetError();


	 gLog = new I_cLog();


#ifdef __ANDROID__
	 gLog->SetDebugFile("sdcard/log.txt");
#endif
	 gLog->SetDebugMode(FILE_MODE);
	 
	 gLog->ResetLog();


	 // Init SDL, Image, TTF, Mix
	 err = InitSDL(GAMEAPI_WINDOW_W,GAMEAPI_WINDOW_H,true);
	 if (err != GAMEAPI_OK)
		{
		 return err;
		}


     rm = new CRandomMersenne((int)time(NULL));


     SDL_version ver;
     SDL_GetVersion(&ver);

	 // anduin init 
	 AndUIn::init(renderer_, false);

	 gAssetManager->Init(renderer_);


	 err = InitAssets();
	 if (err != GAMEAPI_OK)
		{
		 return err;
		}


	 gAssetManager->LoadIntroAssets();
	 gAssetManager->LoadFont();

	 // init main UI
	 uiMain_.AnduinInit();

     err = gGameData.LoadGameData();


	 RenderIntro();


	 b2Vec2 gravity_vec;
	 gravity_vec.Set(0.0, -4.81f);
	 GAMEAPI_world_up = new b2World(gravity_vec);

	 gravity_vec.Set(0.0, 4.81f);
	 GAMEAPI_world_down = new b2World(gravity_vec);



	 // game_state: UI - MAIN
	 gameState_ = GAMESTATE_UI;


	 SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - 70, 10,60,60 };
	 SDL_Color clr = {0,0,0};

	 back_color_.r = 255;
     back_color_.g = 100;
	 back_color_.b = 0;

      Mix_Volume(0,20);
  
    SDL_Rect rct = GAMEAPI_GetRect(10, GAMEAPI_WINDOW_H - 90, GAMEAPI_WINDOW_W - 20, 70);



    AndUIn::font_ = gAssetManager->GetFont();



    for (int c=0;c<GAMEAPI_LEVEL_COUNT;c++)
        {
			level_forest_[c].texture_background_ = gAssetManager->GetWorldBackground(WORLD_FOREST);
			level_winter_[c].texture_background_ = gAssetManager->GetWorldBackground(WORLD_WINTER);
			level_desert_[c].texture_background_ = gAssetManager->GetWorldBackground(WORLD_DESERT);
			level_graveyard_[c].texture_background_ = gAssetManager->GetWorldBackground(WORLD_GRAVEYARD);
			level_candyland_[c].texture_background_ = gAssetManager->GetWorldBackground(WORLD_CANDYLAND);
		}


	// Load finished

    InitLevels();
    wip_BindLevels();

	SetUpdate(true);

	int vol = GAMEAPI_GetPercentage(10, MIX_MAX_VOLUME);

	vol = Mix_VolumeMusic(vol);


	gSoundBlaster.PlayMainMenu();
   

	GAMEAPI_InitVersion();

 return 0;
}
//______________________________________________________________________________________________//




void I_cEngine::RenderIntro(void)
{

	SDL_RenderClear(renderer_);

	int posx = GAMEAPI_GetPercentage(10, GAMEAPI_WINDOW_W);
	int posy = GAMEAPI_GetPercentage(10, GAMEAPI_WINDOW_H);
	int sizew = GAMEAPI_GetPercentage(70, GAMEAPI_WINDOW_W);
	int sizeh = GAMEAPI_GetPercentage(70, GAMEAPI_WINDOW_W);

	SDL_Rect dest = GAMEAPI_GetRect(GAMEAPI_WINDOW_W/2-sizew/2, sizeh/2, sizew, sizeh);
	SDL_RenderCopy(renderer_, gAssetManager->GetSplash(), NULL, &dest);



	SDL_Texture *loading = GAMEAPI_GetStringTexture("Now Loading...", AndUIn::White);


    int text_pos_x = GAMEAPI_GetPercentage(50, GAMEAPI_WINDOW_W);
    int text_pos_w = GAMEAPI_GetPercentage(48, GAMEAPI_WINDOW_W);
    int text_pos_h = GAMEAPI_GetPercentage(5, GAMEAPI_WINDOW_H);
    int text_pos_y = GAMEAPI_WINDOW_H - text_pos_h;
	SDL_Rect rc = GAMEAPI_GetRect(text_pos_x,text_pos_y,text_pos_w,text_pos_h);
	SDL_RenderCopy(renderer_, loading, NULL, &rc);


	SDL_RenderPresent(renderer_);
}



// Init levels
void I_cEngine::InitLevels(void)
{
	int animal = 0;
	for (int c=0;c< GAMEAPI_LEVEL_COUNT;c++)
	    {
		   level_forest_[c].Init(gAssetManager->GetAnimal((GAMEAPI_ANIMAL)animal), mAnimalStringMap[animal],WORLD_FOREST,c);
			 animal++;
			}


	for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
	{
		level_winter_[c].Init(gAssetManager->GetAnimal((GAMEAPI_ANIMAL)animal), mAnimalStringMap[animal], WORLD_WINTER, c);
		animal++;
	}

	for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
	{
		level_desert_[c].Init(gAssetManager->GetAnimal((GAMEAPI_ANIMAL)animal), mAnimalStringMap[animal], WORLD_DESERT, c);
		animal++;
	}

	for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
	{
		level_graveyard_[c].Init(gAssetManager->GetAnimal((GAMEAPI_ANIMAL)animal), mAnimalStringMap[animal], WORLD_GRAVEYARD, c);
		animal++;
	}

	for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
	{
		level_candyland_[c].Init(gAssetManager->GetAnimal((GAMEAPI_ANIMAL)animal), mAnimalStringMap[animal], WORLD_CANDYLAND, c);
		animal++;
	}




	
}



void I_cEngine::OnStartLevel(void *ptr_data)
{


 GAMEAPI_EVENT_DATA *data = (GAMEAPI_EVENT_DATA*)ptr_data;
 gSoundBlaster.StopMusic();
 gSoundBlaster.PlayPop();

  switch (gGameData.GetCurrentWorld())
         {
					case WORLD_FOREST:
					 current_level_ = &level_forest_[data->id];
					 gSoundBlaster.PlayForestMusic();
					break;

					case WORLD_WINTER:
						current_level_ = &level_winter_[data->id];
						gSoundBlaster.PlayWinterMusic();
						break;

					case WORLD_DESERT:
						current_level_ = &level_desert_[data->id];
						gSoundBlaster.PlayDesertMusic();
						break;

					case WORLD_GRAVEYARD:
						current_level_ = &level_graveyard_[data->id];
						gSoundBlaster.PlayGraveMusic();
						break;

					case WORLD_CANDYLAND:
						current_level_ = &level_candyland_[data->id];
						gSoundBlaster.PlayCandyMusic();
						break;
		      }


 if (current_level_)
     current_level_->Reset(); 

	gGameData.SetCurrentLevel(data->id);
	uiMain_.SetMenuState(GAMEAPI_UI_IDLE);
	SetGameState(GAMESTATE_RUNNING);
	StartTimers();
	SetUpdate(true);


	printf("I_cEngine::OnStartLevel\n");
}




// bind all events to receptors
void I_cEngine::wip_BindLevels(void)
{
 for (int c=0;c<GAMEAPI_LEVEL_COUNT;c++)
     {
	   I_cButton *btn = (I_cButton*)uiMain_.gui_wnd_forest_level_select->GetControl(c);
	   btn->OnClick.bind(this, &I_cEngine::OnStartLevel);

	  btn = (I_cButton*)uiMain_.gui_wnd_winter_level_select->GetControl(c);
	  btn->OnClick.bind(this, &I_cEngine::OnStartLevel);

	  btn = (I_cButton*)uiMain_.gui_wnd_desert_level_select->GetControl(c);
	  btn->OnClick.bind(this, &I_cEngine::OnStartLevel);

	  btn = (I_cButton*)uiMain_.gui_wnd_graveyard_level_select->GetControl(c);
	  btn->OnClick.bind(this, &I_cEngine::OnStartLevel);

	  btn = (I_cButton*)uiMain_.gui_wnd_candyland_level_select->GetControl(c);
	  btn->OnClick.bind(this, &I_cEngine::OnStartLevel);
     }

}


GAMEAPI_ERROR I_cEngine::InitSDL(int w, int h, bool fs)
{
	int a = 121 % 25;


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0)
	   {
		return GAMEAPI_ERROR_SDL_INIT;
	   }



#ifdef __ANDROID__

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	GAMEAPI_WINDOW_W = DM.w;
	GAMEAPI_WINDOW_H = DM.h;
	//int Width = DM.w;
	//int Height = DM.h;
	window_ = SDL_CreateWindow("Balloon-Pop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
#else
	window_ = SDL_CreateWindow("Critterz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H, SDL_WINDOW_SHOWN );
#endif

	if (!window_)
	   {
		SDL_Quit();
		return GAMEAPI_ERROR_CREATE_WINDOW;
	   }

	//renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_)
	   {
		  SDL_DestroyWindow(window_);
		  SDL_Quit();
		  return GAMEAPI_ERROR_CREATE_RENDER;
	   }


		 SDL_version ver;
		 SDL_GetVersion(&ver);


	int ret = IMG_Init(IMG_INIT_PNG);
	if (ret < 0)
	   {
	    return GAMEAPI_ERROR_IMG_INIT;
	   }


	ret = TTF_Init();
	if (ret < 0)
   	   {
		return GAMEAPI_ERROR_TTF_INIT;
	   }


 // TODO: fixthis
#ifdef __ANDROID__
	string str_and_font = "font.ttf";
#else
	string str_and_font = "data/font.ttf";
#endif

	AndUIn::font_ = TTF_OpenFont(str_and_font.c_str(), 8);
	if (!AndUIn::font_)
	{
		return GAMEAPI_ERROR_TTF_INIT;
	}

	AndUIn::font_ol_ = TTF_OpenFont(str_and_font.c_str(), 48);
	if (!AndUIn::font_ol_)
	{
		return GAMEAPI_ERROR_TTF_INIT;
	}


	ret = Mix_Init(MIX_INIT_OGG);


	string s = Mix_GetError();
	gLog->AppendLog("ENGINE: %s",s.c_str());
	ret = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	if (ret < 0)
	   {
		return GAMEAPI_ERROR_MIX_INIT;
	   }

	// volume
	Mix_Volume(0, 50);


	SetGameState(GAMESTATE_UI);


	 AndUIn::ANDUIN_Window_W = GAMEAPI_WINDOW_W;
	 AndUIn::ANDUIN_Window_H = GAMEAPI_WINDOW_H;

	 GAMEAPI_Init();

 return GAMEAPI_OK;
}
//______________________________________________________________________________________________//


//==============================================================================================//
//=====================[ INIT ASSETS ]==========================================================//
//==============================================================================================//
GAMEAPI_ERROR I_cEngine::InitAssets(void)
{
	//GAMEAPI_ERROR err = GAMEAPI_OK;



	gAssetManager->LoadAssets();
	//if (err != GAMEAPI_OK)
	//   {
	//    gLog->AppendLog("I_cEngine::InitAssets: Error loading assets.");
	//	return err;
	//   }
	return GAMEAPI_OK;
}
//______________________________________________________________________________________________//



void I_cEngine::RenderUI(void)
{
 if (uiMain_.current_ui_state_ == GAMEAPI_UI_PAUSED)
	  current_level_->Draw(update_);

 uiMain_.Draw();

}




//==============================================================================================//
//=====================[ RENDER ]===============================================================//
//==============================================================================================//
void I_cEngine::Render(void)
{

	SDL_RenderClear(renderer_);
	
	SDL_Rect lvl_rect = { 0,0,GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H };

	
	if (current_level_ && gameState_ == GAMESTATE_RUNNING) // samo ako igra radi
	{
	 current_level_->Draw(update_);
	}

	RenderUI();

    
	char str_fps[64];
	sprintf(str_fps, "FPS: %d", framerate.GetFPS());

    if (gameState_ != GAMESTATE_RUNNING)
       {
        SDL_Rect rc = GAMEAPI_GetRect(10,GAMEAPI_WINDOW_H-30,GAMEAPI_WINDOW_W/4,15);
        SDL_RenderCopy(renderer_,GAMEAPI_TextureVersionText,0,&rc);
       }

	//stringRGBA(renderer_, 10, 10, str_fps, 255, 0, 0, 255);
	//stringRGBA(renderer_, 10, 10, GAMEAPI_VersionString.c_str(), 255, 0, 0, 255);
    

	SDL_RenderPresent(renderer_);

}
//______________________________________________________________________________________________//



//==============================================================================================//
//=====================[ HANDLE EVENTS ]========================================================//
// Izvrsi event u ondnosu na game state
//==============================================================================================//
void I_cEngine::HandleEvents(GAMEAPI_EVENT_TYPE type, void *ptr_data)
{
	switch (gameState_)
	{


	case GAMESTATE_RUNNING:
        HandleEvents_GameStateRunning(type,ptr_data);
		break;

	case GAMESTATE_UI:
		HandleEvents_GameStateUI(type,ptr_data);
		break;


	case GAMESTATE_WALK_OF_SHAME:
		KillTimers();
 	    break;

	case GAMESTATE_TAP_TO_CONTINUE:
		 KillTimers();
		 //HandleEvents_TapToContinue(type);
		 break;


	default: break;
	}

}
//______________________________________________________________________________________________//





//==============================================================================================//
//=====================[ HANDLE EVENTS: UI ]====================================================//
//==============================================================================================//
void I_cEngine::HandleEvents_GameStateUI(GAMEAPI_EVENT_TYPE type, void *ptr_data)
{
    //gLog->AppendLog("I_cEngine::HandleEvents_GameStateUI");

	GAMEAPI_EVENT event;
	event.type = type;
	event.ptr_data = ptr_data;


	switch (event.type)
	{

	 case GAMEAPI_EVENT_LMOUSE_UP:
	      {
		    gAnduin->HandleEvent(AndUIn::EVENT_BUTTON_UP);
		   break;
		  }

	 case GAMEAPI_EVENT_LMOUSE_DOWN:
	 {
		 gAnduin->HandleEvent(AndUIn::EVENT_BUTTON_DOWN);
		 break;
	 }

	 // prikazi WorldCompleteWindow
	 case GAMEAPI_EVENT_WORLD_COMPLETE:
	 {
	   delete uiMain_.gui_wnd_world_complete;
		 uiMain_.CreateWorldCompleteWindow();
		 
		 SetGameState(GAMESTATE_UI);
		 SetMenuState(GAMEAPI_UI_WORLD_COMPLETE);
	  break;
	 }


	 case GAMEAPI_EVENT_GAME_FINISHED:
         SetGameState(GAMESTATE_UI);
         uiMain_.SetMenuState(GAMEAPI_UI_PHASE_OVER);
		 break;


   case GAMEAPI_EVENT_PHASE_FINISHED:
	   ReinitPhase();
	   break;

	 case GAMEAPI_EVENT_SET_UI_STATE:
	 {
		 GAMEAPI_EVENT_DATA *ptr_event_data = (GAMEAPI_EVENT_DATA*) ptr_data;
	   uiMain_.SetMenuState((GAMEAPI_UI_STATE)ptr_event_data->id);
		 delete ptr_event_data;
		 break;
	}

	// iz LevelCompleteWindow
	case GAMEAPI_EVENT_ON_NEXT_LEVEL:
	{
	 OnNextLevel(NULL);
	 break;
	}

	// iz WorldCompleteWindow
	case GAMEAPI_EVENT_WORLD_COMPLETE_CONTINUE:
	{
	 OnWorldComplete(NULL);
	 break;
	}

	case GAMEAPI_EVENT_WORLD_SELECT:
	{
	 gSoundBlaster.PlayPop();
	 OnWorldSelect(ptr_data);
	 break;
	}

	case GAMEAPI_EVENT_RESUME_GAME:
		gSoundBlaster.PlayPop();
		OnResume(NULL);
	 break;

	case GAMEAPI_EVENT_QUIT_CURRENT_GAME:

		QuitCurrentGame(NULL);
	 break;


	 case GAMEAPI_EVENT_QUIT_GAME:
		gSoundBlaster.PlayPop();
	  OnQuit();
		break;


	 case GAMEAPI_EVENT_SHOW_COLLECTION:
		 gSoundBlaster.PlayPop();
		 OnCollections();
		break;

	 case GAMEAPI_EVENT_START_GAME:
		 gSoundBlaster.PlayPop();
		 OnStartGame();
		break;

	 case GAMEAPI_EVENT_SHOW_OPTIONS:
		 gSoundBlaster.PlayPop();
		 OnOptions();
		break;

	 // TODO: OnResetGame(confirm)
	 case GAMEAPI_EVENT_RESET_GAME:
		 gSoundBlaster.PlayPop();
       OnResetGame();
		break;

		case GAMEAPI_EVENT_SHOW_CREDITS:
			OnCredits();
		 break;

 
     case GAMEAPI_EVENT_CREATE_WINNER_BALLOON:
     {
      uiMain_.gui_wnd_winner->CreateBalloon();
      break;
     }


	 default:
	 break;

	}
	
}
//______________________________________________________________________________________________//




void I_cEngine::OnResetGame(void)
{
   uiMain_.SetMenuState(GAMEAPI_UI_RESET_SELECT);

}


// ON: PhaseOverWindow::OnContinue
void I_cEngine::ReinitPhase(void)
{
	gSoundBlaster.PlayPop();
	gSoundBlaster.StopChannel(1); // stop sfx
	gSoundBlaster.StopMusic();  // stop level music
	gSoundBlaster.PlayMainMenu(); // play theme 

	uiMain_.ReinitPhase();


	 for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
	 {
		 level_forest_[c].Reinit();
		 level_winter_[c].Reinit();
		 level_desert_[c].Reinit();
		 level_graveyard_[c].Reinit();
		 level_candyland_[c].Reinit();
	 }

	 uiMain_.SetMenuState(GAMEAPI_UI_MAIN_MENU);
	 SetGameState(GAMESTATE_UI);

}

//==============================================================================================//
//=====================[ HANDLE EVENTS: RUNNING ]===============================================//
// GameRunningState: 
// CALLED: HandleEvents(RUNNING)
// *
// Handles engine states when game is running.
// TODO: seperate engine and UI states
// *
//==============================================================================================//
void I_cEngine::HandleEvents_GameStateRunning(GAMEAPI_EVENT_TYPE type, void *ptr_data)
{
	GAMEAPI_EVENT event;

	event.type = type;
	event.ptr_data = ptr_data;
	
    switch (event.type)
	  	   {

		    case GAMEAPI_EVENT_LEVEL_COMPLETE:
		    {

               int count = current_level_->GetStarCount();
               uiMain_.gui_wnd_level_complete->SetStarCount(count);
			   uiMain_.gui_wnd_level_complete->Update();
			   SetGameState(GAMESTATE_UI);
			   SetMenuState(GAMEAPI_UI_LEVEL_COMPLETE);
			   KillTimers();
		     break;
		    }
			
		   case GAMEAPI_EVENT_CREATE_BALLOON:
		   {
			  current_level_->CreateBalloon();
			  break;
		   }




		// NOTE: seperate the letters from engine, maybe put them in level.
		case GAMEAPI_EVENT_CREATE_LETTER:
		{
			I_cBalloon *ptr_balloon = (I_cBalloon*)event.ptr_data;

			I_cLetter *letter = new I_cLetter();
			letter->Init(ptr_balloon->balloon_rect_.x + ptr_balloon->balloon_rect_.w/2 ,ptr_balloon->balloon_rect_.y + ptr_balloon->balloon_rect_.h/2, GAMEAPI_GetColor(255,255,0));
			current_level_->vLetterList.push_back(letter);

			// NOTE: we should really 
			//delete ptr_balloon;   // here

			break;
		}

		// TODO: Fix all of this. redundant
		case GAMEAPI_EVENT_CREATE_JOKER:
		{
			SDL_Rect *ptr_rect = (SDL_Rect*)event.ptr_data; // ugh, just ... why?

			I_cLetter *letter = new I_cLetter();
			letter->Init(ptr_rect->x + ptr_rect->w / 2, ptr_rect->y + ptr_rect->h / 2,GAMEAPI_GetColor(0,255,0));
			letter->SetLetter(current_level_->GetRandomTextBarLetter());
			current_level_->vLetterList.push_back(letter);
            delete ptr_rect;
			break;

		}

		// on animal click
		case GAMEAPI_EVENT_POP_ANIMAL:
		{
			GAMEAPI_ANIMAL *ptr_ani = (GAMEAPI_ANIMAL*)event.ptr_data;
			gGameData.SetAnimalCollected(gGameData.GetCurrentWorld(), gGameData.GetCurrentLevel(),1);
			delete ptr_ani;
		  break;
		}



		case GAMEAPI_EVENT_LMOUSE_UP:
		{
		    // we what?
			current_level_->OnClick(mouse_x_, mouse_y_);// balloon pop
		    current_level_->OnClick_Letter(mouse_x_,mouse_y_);// letter pop

		  // ovdhe hndlamo za pause button
 		  gAnduin->HandleEvent(AndUIn::EVENT_BUTTON_UP);
		  break;
		 }


		// debug, not used in release
		case GAMEAPI_EVENT_RMOUSE_CLICK:
		{
			GAMEAPI_CallEvent(GAMEAPI_EVENT_LEVEL_COMPLETE,0);
			//current_level_->CreateBalloon();
			break;
		}


		case GAMEAPI_EVENT_PAUSE_GAME:
			OnPauseGame(ptr_data);
			break;

		case GAMEAPI_EVENT_QUIT:
            Stop();
			break;




		case GAMEAPI_EVENT_KEY_TEST_KEY:
		{
			break;
		}

		default: break;
		}
       
}
//______________________________________________________________________________________________//








// Balloons are created on intervasl
Uint32 I_cEngine::OnTimer_AddBalloon(Uint32 interval, void *param)
{
 I_cEngine *ptr_engine = (I_cEngine*)param;
 if (ptr_engine->GetUpdate())
    {
     GAMEAPI_CallEvent(	GAMEAPI_EVENT_CREATE_BALLOON, NULL);
    }


 return(interval);
}



Uint32 I_cEngine::OnTimer_GameTimer(Uint32 interval, void *param)
{
 GAMEAPI_Event event_timer;
 event_timer.type = GAMEAPI_EVENT_UPDATE_TIME;
 GAMEAPI_CallEvent(GAMEAPI_EVENT_UPDATE_TIME,NULL);
 //GAMEAPI_PushEvent(event_timer);


 return interval;
}






//==============================================================================================//
//=====================[ RESET GAME ]===========================================================//
//==============================================================================================//
void I_cEngine::ResetGame(void)
{
	gSoundBlaster.PlayPop();

  current_level_->Reset();

	KillTimers();
	StartTimers();
	SetUpdate(true);
	gameState_ = GAMESTATE_RUNNING;

}
//______________________________________________________________________________________________//




// Engine is running
bool I_cEngine::IsRunning()
{
	return run_;
}


// Stop the engine; exit game
void I_cEngine::Stop(void)
{
    gGameData.SaveGameData();
	run_ = false;
}


// UI or RUNNING
void I_cEngine::SetGameState(GAMEAPI_GAMESTATE state)
{
	gameState_ = state;
}


GAMEAPI_GAMESTATE I_cEngine::GetGameState(void)
{
	return gameState_;
}

// UI State: Resume Game | Start Game
void I_cEngine::SetMenuState(GAMEAPI_UI_STATE state)
{
	uiMain_.SetMenuState(state);
}

// UI State: Reset game data
// TODO: options
void I_cEngine::OnOptions(void)
{
 uiMain_.SetMenuState(GAMEAPI_UI_SETTINGS_SELECT);

}



void I_cEngine::OnCredits(void)
{
	gSoundBlaster.PlayPop();
	uiMain_.SetMenuState(GAMEAPI_UI_CREDITS);


	/*
	for (int c = 0, count = 0; c < WORLD_COUNT; c++)
	{
		printf("world[%d].finished = %d\n",c, gGameData.worldData_[c].finished);

		for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
		{
		 printf("\t level[%d].finished = %d --- level[%d].star_count = %d\n",i, gGameData.worldData_[c].levelData[i].finished,i, gGameData.worldData_[c].levelData[i].star_num);
		}
	}*/

}

// CALLED: UI event loop
void I_cEngine::OnCollections(void)
{
	printf("Credits\n");
	uiMain_.SetMenuState(GAMEAPI_UI_COLLECTIONS_SELECT);

}


// REMOVE 16.8.20129
void I_cEngine::OnBalloonCollections(void *ptr_data)
{
	uiMain_.SetMenuState(GAMEAPI_UI_ANIMAL_COLLECTION_SELECT);

}

// back to void
void I_cEngine::OnQuit(void)
{
	printf("Quit\n");
	KillTimers();
	Stop();
}


// CALLED: UI event loop
void I_cEngine::OnResume(void *ptr_data)
{
	SetGameState(GAMESTATE_RUNNING);
	uiMain_.SetMenuState(GAMEAPI_UI_IDLE); // IDLE znaci da samo crtamo menu_back
	current_level_->update_ = true;
	SetUpdate(true);
}

void I_cEngine::OnPauseGame(void *ptr_data)
{
	uiMain_.SetMenuState(GAMEAPI_UI_PAUSED);
	SetGameState(GAMESTATE_UI);
	current_level_->update_ = false;
	SetUpdate(false); // nemoj updatati igru ali svejedno prikazi nivo
}


void I_cEngine::QuitCurrentGame(void *ptr_data)
{
	gSoundBlaster.PlayPop();
	gSoundBlaster.StopChannel(1); // stop sfx
	gSoundBlaster.StopMusic();  // stop level music
	gSoundBlaster.PlayMainMenu(); // play theme 

    current_level_->Reset();
	uiMain_.SetMenuState(GAMEAPI_UI_MAIN_MENU);
	SetGameState(GAMESTATE_UI);
	KillTimers();
}




// DEPRECATED: refactor
void I_cEngine::OnBackToCollections(void *ptr_data)
{
	uiMain_.SetMenuState(GAMEAPI_UI_COLLECTIONS_SELECT);
	SetGameState(GAMESTATE_UI);

}



// DEPRECATED: refactor
void I_cEngine::OnStartGame(void)
{
	uiMain_.SetMenuState(GAMEAPI_UI_WORLD_SELECT);
	SetGameState(GAMESTATE_UI);

}


// CALLED: UI event loop
// ptr_data: button->id -> I_cWorldSelesct::Init()
void I_cEngine::OnWorldSelect(void *ptr_data)
{
 GAMEAPI_EVENT_DATA *data = (GAMEAPI_EVENT_DATA*)ptr_data;
 switch (data->id)
		{
		 case WORLD_FOREST:
		  {
			 uiMain_.SetMenuState(GAMEAPI_UI_FOREST_LEVEL_SELECT);
			 uiMain_.selected_world_type_ = WORLD_FOREST;
			 current_level_ = &level_forest_[gGameData.GetCurrentLevel()];
			 gSoundBlaster.StopMusic();
			 gSoundBlaster.PlayForestBackground();
			}
		break;

		 case WORLD_WINTER:
		     
			 uiMain_.SetMenuState(GAMEAPI_UI_WINTER_LEVEL_SELECT);
			 current_level_ = &level_winter_[gGameData.GetCurrentLevel()];
			 gSoundBlaster.StopMusic();
			 gSoundBlaster.PlayWinterBackground();
			 break;

		 case WORLD_DESERT:
			 uiMain_.SetMenuState(GAMEAPI_UI_DESERT_LEVEL_SELECT);
			 current_level_ = &level_desert_[gGameData.GetCurrentLevel()];
			 gSoundBlaster.StopMusic();
			 gSoundBlaster.PlayWinterBackground();
			 break;

		 case WORLD_GRAVEYARD:
			 uiMain_.SetMenuState(GAMEAPI_UI_GRAVEYARD_LEVEL_SELECT);
			 current_level_ = &level_graveyard_[gGameData.GetCurrentLevel()];
			 gSoundBlaster.StopMusic();
			 gSoundBlaster.PlayGraveBackground();
			 break;

		 case WORLD_CANDYLAND:
			 uiMain_.SetMenuState(GAMEAPI_UI_CANDYLAND_LEVEL_SELECT);
			 current_level_ = &level_candyland_[gGameData.GetCurrentLevel()];
			 gSoundBlaster.StopMusic();
			 gSoundBlaster.PlayForestBackground();
			 break;
		}

	gGameData.SetCurrentWorld(data->id);

	//NOTE:  useless here
	I_cLevelSelectWindow *wnd_level_select = uiMain_.GetLevelSelectWindow((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld());


  
}



void I_cEngine::OnBack_FromLevelSelect(void *ptr_data)
{
    gSoundBlaster.StopChannel(1);
	gSoundBlaster.PlayMainMenu();
	uiMain_.SetMenuState(GAMEAPI_UI_WORLD_SELECT);
	SetGameState(GAMESTATE_UI);
}







// Reset life, check if game over, If last evevel of the  world. call WORLD_COMPLETE
void I_cEngine::OnNextLevel(void *ptr_data) 
{
   int cur_level, cur_world;
   cur_level = gGameData.GetCurrentLevel();
   cur_world = gGameData.GetCurrentWorld();
   int star_num = current_level_->GetStarCount();
	
	int prev_star_num = gGameData.GetStarCount(cur_world,cur_level);

	// Disable last lowest value
	if (star_num > prev_star_num || prev_star_num == 255) // uint8_t -1 - default
	   {
	    gGameData.SetLevelFinished(star_num);
        
	    if (gGameData.IsGameOver() == true)
	       {
            current_level_->Reset();
		    GAMEAPI_CallEvent(GAMEAPI_EVENT_GAME_FINISHED, 0);
		    return;
	       }
	   }

    // updateaj stars za na level select
	I_cLevelSelectWindow *current_level_select_wnd = uiMain_.GetLevelSelectWindow((GAMEAPI_WORLD_TYPE)cur_world);
	current_level_select_wnd->SetStarCount(cur_level,gGameData.GetStarCount(cur_world,cur_level));



	// next world?
	cur_level = gGameData.NextLevel();
	if (gGameData.GetCurrentLevel() == GAMEAPI_LEVEL_COUNT)
		 {
			gGameData.ResetLevel();
			GAMEAPI_CallEvent(GAMEAPI_EVENT_WORLD_COMPLETE, 0);
			return;
		 }



    // menu is now current world
    switch((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld())
          {
					 case WORLD_FOREST:
						uiMain_.SetMenuState(GAMEAPI_UI_FOREST_LEVEL_SELECT);
						break;
					case WORLD_WINTER:
						uiMain_.SetMenuState(GAMEAPI_UI_WINTER_LEVEL_SELECT);
						break;
					case WORLD_DESERT:
						uiMain_.SetMenuState(GAMEAPI_UI_DESERT_LEVEL_SELECT);
						break;
					case WORLD_GRAVEYARD:
						uiMain_.SetMenuState(GAMEAPI_UI_GRAVEYARD_LEVEL_SELECT);
						break;
					case WORLD_CANDYLAND:
						uiMain_.SetMenuState(GAMEAPI_UI_CANDYLAND_LEVEL_SELECT);
						break;
					}

     current_level_->Reset();
	 gGameData.ResetCounters();
	 gGameData.SaveGameData();
}



void I_cEngine::OnWorldComplete(void *ptr_data)
{
     gGameData.SetWorldFinished(gGameData.GetCurrentWorld());
     gGameData.SetInProgress(gGameData.GetCurrentWorld(),false);


     if (gGameData.IsGameOver() && gGameData.GetCurrentWorld() == WORLD_CANDYLAND)
        {
	     // Winner
	     GAMEAPI_CallEvent(GAMEAPI_EVENT_GAME_FINISHED,0);
	     return;
	    }
           
 gGameData.NextWorld();


 gGameData.SetInProgress(gGameData.GetCurrentWorld(), true);
 uiMain_.gui_wnd_world_select->ReinitPhase();

 gSoundBlaster.StopAll();

 int cur_world = gGameData.GetCurrentWorld();

 // NOTE we have to manually set background for level_complete
 switch((GAMEAPI_WORLD_TYPE)cur_world)
       {
	    case WORLD_FOREST:
			  // NOTE: if current_world is FOREST that the world counter looped back.
			  // In the case we didn't collect all 3 starr, just show the main menu
              SetGameState(GAMESTATE_UI);
              SetMenuState(GAMEAPI_UI_MAIN_MENU);
			break;
		
		case WORLD_WINTER:
			uiMain_.gui_wnd_level_complete->SetBackgroundTexture(gAssetManager->GetWorldBackground(WORLD_WINTER));
			uiMain_.gui_wnd_winter_level_select->SetMarkerPos(0);
			uiMain_.SetMenuState(GAMEAPI_UI_WINTER_LEVEL_SELECT);

			gSoundBlaster.PlayWinterBackground();
		 break;

		case WORLD_DESERT:
			uiMain_.gui_wnd_level_complete->SetBackgroundTexture(gAssetManager->GetWorldBackground(WORLD_DESERT));
			uiMain_.gui_wnd_desert_level_select->SetMarkerPos(0);
			uiMain_.SetMenuState(GAMEAPI_UI_DESERT_LEVEL_SELECT);

	         gSoundBlaster.PlayDesertBackground();
			break;


		case WORLD_GRAVEYARD:
			uiMain_.gui_wnd_level_complete->SetBackgroundTexture(gAssetManager->GetWorldBackground(WORLD_GRAVEYARD));
			uiMain_.gui_wnd_graveyard_level_select->SetMarkerPos(0);
			uiMain_.SetMenuState(GAMEAPI_UI_GRAVEYARD_LEVEL_SELECT);

			gSoundBlaster.PlayGraveBackground();
			break;


		case WORLD_CANDYLAND:
			uiMain_.gui_wnd_level_complete->SetBackgroundTexture(gAssetManager->GetWorldBackground(WORLD_CANDYLAND));
			uiMain_.gui_wnd_candyland_level_select->SetMarkerPos(0);
			uiMain_.SetMenuState(GAMEAPI_UI_CANDYLAND_LEVEL_SELECT);

			gSoundBlaster.PlayCandyBackground();
			break;

		}


}

// HACK to disable level repeat 
void I_cEngine::onClick_EmptyFunc_tmp(void *ptr_data)
{
	// dummy - ne radi nissta
}


void I_cEngine::SetUpdate(bool update)
{
 update_ = update;

}


bool I_cEngine::GetUpdate(void)
{
 return update_;
}



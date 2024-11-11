

#define SDL_MAIN_HANDLED
#include <iostream>

#include "include/gameapi.h"
#include "include/I_cEngine.h"
#include "include/I_cLog.h"
#include "include/AndUIn/anduin.h"
#include "include/AndUIn/I_cAnduin.h"




int main()
{

	int err = 0;
	int frames = 0;
	char str_fps[32] = {};
	uint32_t start = 0;
	SDL_Event sdlEvent_;
	AndUIn::ANDUIN_Event anduinEvent_;
	
	
    gAssetManager = new I_cAssetManager();
	gAnduin = new I_cAndUIn();

	I_cEngine *gameEngine = new I_cEngine();
	gameEngine->Init();

	
	while (gameEngine->IsRunning())
	{
		start = SDL_GetTicks();
		
		while (SDL_PollEvent(&sdlEvent_))
		{
			switch (sdlEvent_.type)
			{
			case SDL_QUIT:
				gameEngine->Stop();
				break;


			case SDL_KEYDOWN:
			{
				switch (sdlEvent_.key.keysym.sym)
				{
				 // temp. should not be here in the release
				 case SDLK_ESCAPE:
					break;
				}
			
			 break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				if (sdlEvent_.button.button == 1) // left  up
					gameEngine->HandleEvents(GAMEAPI_EVENT_LMOUSE_UP,0);

			 break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				if (sdlEvent_.button.button == 1) // left down
					 gameEngine->HandleEvents(GAMEAPI_EVENT_LMOUSE_DOWN, 0);
				else gameEngine->HandleEvents(GAMEAPI_EVENT_RMOUSE_CLICK, 0);

			break;
			}


			case SDL_MOUSEMOTION:
			{
				gameEngine->mouse_x_ = sdlEvent_.motion.x;
				gameEngine->mouse_y_ = sdlEvent_.motion.y;

			 break;
			}

			case SDL_USEREVENT:
			{
				gameEngine->HandleEvents((GAMEAPI_EVENT_TYPE)sdlEvent_.user.code, sdlEvent_.user.data1);

 			 break;
			}

			default: break;
			}
			
		}

		
		gameEngine->Render();
		gameEngine->framerate.Update();

		if (gameEngine->GetUpdate() == true)  // not paused
		   {
			  GAMEAPI_world_up->Step((float32)(1.0 / GAMEAPI_FPS), 8, 3);
			  GAMEAPI_world_down->Step((float32)(1.0 / GAMEAPI_FPS), 8, 3);
			 }
		

		if (GAMEAPI_FPS_STEP > SDL_GetTicks() - start)
			SDL_Delay((uint32_t)(GAMEAPI_FPS_STEP - (SDL_GetTicks() - start)));


		sprintf(str_fps, "FPS: %d", gameEngine->framerate.GetFPS());  // snprintf
		SDL_SetWindowTitle(gameEngine->window_, str_fps);

	}

#ifdef __ANDROID__
	//if (app)
	//	delete app;

#endif


	delete gameEngine;
	
	exit(0);
}



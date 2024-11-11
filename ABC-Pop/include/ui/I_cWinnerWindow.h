#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"
#include "include/I_cStars.h"
#include "include/I_cText.h"
#include "include/I_cBalloon.h"
#include "include/I_cStarDroplet.h"
#include <list>


class I_cWinnerWindow : public I_cWindow
{
public:
   I_cWinnerWindow();
  ~I_cWinnerWindow();




	void Init(void);
	void Draw(void);
    void OnClose(void); // lose focus end timer
    void OnShow(void);

	I_cButton *butt_continue;


    I_cPicture* pic_frame;
    I_cPicture* pic_panel;

    list<I_cBalloon*>vBalloonList;
    list <I_cStarDroplet*> vStarList;

	void OnContinue(void *ptr_data);
    void CreateBalloon(void);
    static Uint32 OnTimer_CreateBalloon(Uint32 interval, void *param);
    SDL_TimerID timerId_;
    void DrawStars(void);

    
	vector<SDL_Texture*>vWinnerStringList;
};
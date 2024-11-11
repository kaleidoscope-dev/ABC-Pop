#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"
#include "include/I_cStars.h"
#include "include/I_cText.h"


typedef struct LETTER
{
 SDL_Texture *texLetter;
 SDL_Texture *texQuestion;
 SDL_Rect loc;
 bool question;
}LETTER;


class I_cPhaseOverWindow : public I_cWindow
{
public:
   I_cPhaseOverWindow();
	~I_cPhaseOverWindow();


	void Init(void);
	void Draw(void);
    void OnShow(void);

	I_cButton *butt_continue;
   SDL_Texture* tex_stat_panel;
   SDL_Texture* tex_forest_frame;


   I_cPicture* pic_frame;
   I_cPicture* pic_panel;
   I_cPicture* pic_letter_back;

   //vector<I_cStars> vStarBarList;
   vector<I_cPicture*>vPictureList;
   
   vector<LETTER>vLetterList;
   

	void OnContinue(void *ptr_data);

};
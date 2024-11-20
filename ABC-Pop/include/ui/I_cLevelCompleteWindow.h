#pragma once 
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"
#include "anduin/I_cTextBox.h"
#include "anduin/I_cImageButton.h"



class I_cLevelCompleteWindow : public I_cWindow
{
public:
	I_cLevelCompleteWindow();
	~I_cLevelCompleteWindow();



	void Update(void); // update sve vrijednosti
	void Init(void);
	/*
	 void SetStars(int star_num);
	 void SetStats(void);
	 */
	 void Draw(void);


	 I_cPicture *pic_frame;
	 I_cPicture *stat_frame;

   I_cPicture *pic_star[3];

	 I_cPicture *pic_balloon;
	 I_cPicture *pic_balloonq;

	 I_cPicture *pic_miss;
	 I_cPicture *pic_lett_miss;

	 I_cPicture *pic_animal;


	 I_cButton *level_marker;

	 I_cImageButton *butt_continue;
     int star_count_;
	 //I_cTextBox *label_pop;
	 //I_cTextBox *label_miss;
	 //I_cTextBox *label_lett_miss;
	 
     //I_cLabel *label_collect;


     SDL_Texture *tex_pop_;
     SDL_Texture *tex_miss_;
     SDL_Texture *tex_lett_miss_;

     void SetStarCount(int cnt);
	 void tmp_init_stars(void);

	 void OnContinue(void *ptr_data);


   //int star_num_;  // koliko zvijezdica crtamo
};
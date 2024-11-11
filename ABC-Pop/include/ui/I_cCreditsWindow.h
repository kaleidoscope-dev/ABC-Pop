#pragma once 
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"


class I_cCreditsWindow : public I_cWindow
{
public:
	I_cCreditsWindow();
	~I_cCreditsWindow();

	void Init(void);

	void Draw(void);


	I_cButton *butt_next;
	I_cButton *butt_prev;
	I_cButton *btn_back_to_options_;

	int current_window_;

	SDL_Texture *tex_stat_panel;
	SDL_Texture *tex_forest_frame;

	I_cPicture *pic_frame;
	I_cPicture *pic_panel;

	vector<SDL_Texture*>vArtistStringList;
   vector<SDL_Texture*>vCreditsStringList;

	void NextCollection(void *ptr_data);
	void PrevCollection(void *ptr_data);
	void OnBackToOptions(void *ptr_data);
};
#pragma once 
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"
#include "anduin/I_cTextBox.h"
#include "anduin/I_cImageButton.h"
#include <map>


// TODO:
//  mora kao i kolekcije imati listanje prozora za svaki svijet


class I_cDictionaryWindow : public I_cWindow
{
public:
			I_cDictionaryWindow();
			~I_cDictionaryWindow();



			void Init(void);
    	void Draw(void);

 private:

	 I_cButton* btn_return_;

	 void CreateBackButton();
	 void OnReturn(void* ptr_data);



	 I_cButton *butt_next;
	 I_cButton *butt_prev;


	 SDL_Texture *tex_stat_panel;
	 SDL_Texture *tex_forest_frame;

	 I_cPicture *pic_frame;
	 I_cPicture *pic_panel;


	 int current_window_;

	 void NextCollection(void *ptr_data);
	 void PrevCollection(void *ptr_data);

	 vector<I_cImageButton *>vWordList;


};
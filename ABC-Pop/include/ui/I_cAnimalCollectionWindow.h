#pragma once 
#include "anduin/anduin.h"
#include "include/gameapi.h"
#include "anduin/I_cAndUIn.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"

class I_cAnimalCollectionWindow: public I_cWindow
{
public:
	I_cAnimalCollectionWindow();
	~I_cAnimalCollectionWindow();


	void Init(I_cAndUIn *ptr_anduin);


	void Draw(void);


	I_cButton *animal_row1[3];
	I_cButton *animal_row2[3];
	I_cButton *animal_row3[3];
	I_cButton *animal_row4[3];


	I_cButton* btn_return_;

	void CreateBackButton();

	GAMEAPI_EVENT_DATA data[GAMEAPI_BALLOON_TYPE_COUNT];

	I_cButton *butt_next;
	I_cButton *butt_prev;

	I_cPicture *pic_frame;

	vector<I_cPicture *>vAnimalFrameList;
	
	int current_window_;


	void NextCollection(void *ptr_data);
	void PrevCollection(void *ptr_data);

	void OnReturn(void *ptr_data);


	vector<SDL_Rect>vRectList;
};
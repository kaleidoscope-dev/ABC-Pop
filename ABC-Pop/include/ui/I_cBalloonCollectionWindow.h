#pragma once 
#include "anduin/anduin.h"
#include "include/gameapi.h"
#include "anduin/I_cAndUIn.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"

class I_cBalloonCollectionWindow: public I_cWindow
{
public:
	I_cBalloonCollectionWindow();
	~I_cBalloonCollectionWindow();


	void Init(I_cAndUIn *ptr_anduin);


	void OnBalloonClick(void *ptr_data);

	void Draw(void);


	I_cButton *selected_balloon;
	I_cButton *balloons_row1[3];
	I_cButton *balloons_row2[3];


	GAMEAPI_EVENT_DATA data[GAMEAPI_BALLOON_TYPE_COUNT];




};
#pragma once 
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"



class I_cWorldSelectWindow : public I_cWindow
{
public:
	I_cWorldSelectWindow();
	~I_cWorldSelectWindow();

	void Init(void);
   void Init2(void);

	void ReinitPhase(void);

	I_cButton *btn_world_select[WORLD_COUNT];
	I_cPicture *pic_frame;

	void Draw(void);


	I_cButton* btn_return_;

	void CreateBackButton();
	void OnReturn(void* ptr_data);

	void OnForestClick(void *ptr);
	void OnWinterClick(void *ptr);
	void OnDesertClick(void *ptr);
	void OnGraveClick(void *ptr);
	void OnCandyClick(void *ptr);
	void OnClick(void *ptr_data);

};
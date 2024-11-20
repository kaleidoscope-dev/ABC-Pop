#pragma once
#include "anduin/I_cAndUIn.h"
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"



class I_cGameplayWindow : public I_cWindow
{
public:
	I_cGameplayWindow();
	~I_cGameplayWindow();


	void Init(void);

	void Draw(void);


	I_cButton *btn_pause_game;

	void CreateBackButton();

	void OnPauseGame(void *ptr_data);
};
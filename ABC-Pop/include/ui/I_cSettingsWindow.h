#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cCheckButton.h"
#include "anduin/I_cPicture.h"


class I_cSettingsWindow : public I_cWindow
{
public:
	I_cSettingsWindow();
	~I_cSettingsWindow();


	I_cCheckButton *btn_music_;
	I_cCheckButton *btn_sfx_;
	//I_cButton *btn_sfx_;
	I_cButton *btn_reset_game_;
	I_cButton *btn_credits_;
	I_cButton *btn_about_;


	I_cButton* btn_return_;

	void Init(void);

	void Draw(void);
	void CreateBackButton();

	void OnResetGame(void *ptr_data);
	void OnMusicOnOff(void *ptr_data);
	void OnSfxOnOff(void *ptr_data);
	void OnShowCredits(void *ptr_data);
	void OnReturn(void* ptr_data);


	


};

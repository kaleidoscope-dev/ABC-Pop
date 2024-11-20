#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"
#include "anduin/I_cImageButton.h"


class I_cPauseWindow : public I_cWindow
{
public:
	I_cPauseWindow();
	~I_cPauseWindow();


	I_cImageButton *btn_quit_current_game_;
	I_cImageButton *btn_resume_game_;



	void OnResume(void *prt_data);
	void QuitCurrentGame(void *ptr_data);


	void Init(void);

	void Draw(void);

};
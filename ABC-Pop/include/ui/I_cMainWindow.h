#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cPicture.h"
#include "anduin/I_cImageButton.h"

class I_cMainWindow : public I_cWindow
{
public:
	I_cMainWindow();
	~I_cMainWindow();



	void Init(void);

	void Draw(void);

	I_cImageButton *img_button;
	I_cImageButton *btn_start_game_;
	I_cImageButton *btn_show_collections_;
	I_cImageButton *btn_options_;
	I_cImageButton *btn_quit_game_;



	void OnCollections(void *ptr_data);
	void OnQuit(void *ptr_data);
	void OnStartGame(void *ptr_data);
    void OnOptions(void *ptr_data);
	void ReinitPhase(void);
 
    

};
#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cCheckButton.h"
#include "anduin/I_cPicture.h"


class I_cResetMessageWindow : public I_cWindow
{
public:
   I_cResetMessageWindow();
	~I_cResetMessageWindow();


	I_cButton *btn_ok_;
   I_cButton* btn_cancel_;
   I_cButton* btn_return_;

   I_cPicture *panel;



	void Init(void);
	void Draw(void);
   void CreateBackButton(void);

   vector<string> vMessageList;
   vector<SDL_Texture*> vTexList;
   void OnOk(void* ptr_data);
   void OnReturn(void* ptr_data);

};

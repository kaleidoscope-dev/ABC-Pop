#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include "I_cTextBox.h"
#include "I_cButton.h"
#include "I_cLabel.h"
#include "I_cTextBoxInput.h"
#include "I_cWindow.h"
#include "I_cCheckButton.h"
#include "I_cImageButton.h"


using namespace AndUIn;



class I_cAndUIn
{
 public:
	 I_cAndUIn();
	 ~I_cAndUIn();

	
 	 //void init(void);
	 I_cWindow *CreateAnduinWindow(void);
	 void CreateAnduinWindow(I_cWindow *wnd);
	 I_cWidget *CreateWidget(I_cWindow *parent_wnd, ANDUIN_CONTROL_TYPE type);
	 void AddWidget(I_cWindow *parent_wnd, I_cWidget *wdg);

	 void HandleEvent(SDL_Event *event);
	 void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);

	 void Draw(void);
	 I_cWindow *GetActiveWindow(void);
	 void SetActiveWindow(I_cWindow *window);

 private:
	 std::vector<I_cWindow*>vWindowList;

	 void Start(void);


};


extern I_cAndUIn *gAnduin;




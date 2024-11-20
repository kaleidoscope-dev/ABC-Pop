#pragma once
#include "anduin.h"
#include "I_cTextBox.h"



class I_cTextBoxInput : public I_cTextBox
{
 public:
	 I_cTextBoxInput();
	~I_cTextBoxInput();

	
	

private:
	void HandleEvent(SDL_Event *event);


};
#pragma once
#include "I_cLabel.h"
#include "I_cButton.h"
#include "I_cAnduin.h"



class I_cKeyboard 
{
 public:
	 I_cKeyboard();
	~I_cKeyboard();

	 void Init(I_cAndUIn *ptr_and);

	 std::vector<I_cButton*>vKeyList;
	 std::vector<std::string>vABC;
	 SDL_Rect rect_;
	 I_cAndUIn *ptr_anduin_;

};
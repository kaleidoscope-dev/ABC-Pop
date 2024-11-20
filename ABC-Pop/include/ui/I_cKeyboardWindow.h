#pragma once
#include "anduin/I_cAndUIn.h"
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"



class I_cKeyboardWindow : public I_cWindow
{
public:
	I_cKeyboardWindow();
	~I_cKeyboardWindow();


	void Init(I_cAndUIn *ptrAnduin);

	void Draw(void);


	std::vector<I_cButton*>vKeyList;
	std::vector<std::string>vABC;
	SDL_Rect rect_;



};
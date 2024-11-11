#include "I_cKeyboardWindow.h"



I_cKeyboardWindow::I_cKeyboardWindow()
{
}


I_cKeyboardWindow::~I_cKeyboardWindow()
{
}


void I_cKeyboardWindow::Init(I_cAndUIn *ptrAnduin)
{
/*
	rect_.x = 10;
	rect_.y = GAMEAPI_WINDOW_H - 200;
	rect_.w = GAMEAPI_WINDOW_W - 20;
	rect_.h = 70;

	vABC.push_back("a");
	vABC.push_back("b");
	vABC.push_back("c");
	vABC.push_back("d");
	vABC.push_back("e");
	vABC.push_back("f");
	vABC.push_back("g");
	vABC.push_back("h");
	vABC.push_back("i");
	vABC.push_back("j");
	vABC.push_back("k");
	vABC.push_back("l");
	vABC.push_back("m");
	vABC.push_back("n");
	vABC.push_back("o");
	vABC.push_back("p");
	vABC.push_back("r");
	vABC.push_back("s");
	vABC.push_back("t");
	vABC.push_back("u");
	vABC.push_back("w");
	vABC.push_back("x");
	vABC.push_back("y");
	vABC.push_back("z");



	int button_w = (rect_.w / 8);
	int button_h = 40;
	SDL_Rect rc = rect_;


	for (int c=0,j = 0;c<8;c++)
		{
		 for (int i=0;i<3;i++,j++)
		     {
			  I_cButton *button = (I_cButton*)ptrAnduin->CreateWidget(this, ANDUIN_CONTROL_BUTTON);
			  button->SetPos(rc.x + 7 + button_w * c , rc.y +10 + 50* i, button_w - 10, button_h);
			  button->SetText(vABC[j], GAMEAPI_GetColor(255, 255, 255));
			  vKeyList.push_back(button);
			  }
		 }
*/

}


void I_cKeyboardWindow::Draw(void)
{
 I_cWindow::Draw();
}

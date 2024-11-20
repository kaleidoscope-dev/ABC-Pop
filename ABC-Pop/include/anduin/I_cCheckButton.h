#pragma once
#include "anduin.h"
#include "I_cButton.h"
//#include "FastDelegate/FastDelegate.h"
#include <string>

using namespace fastdelegate;

class I_cCheckButton : public I_cButton
{
 public:
	 I_cCheckButton(std::string nameid = "cb_button");
	~I_cCheckButton();


	void SetCheckTexture(SDL_Texture *on, SDL_Texture *off);
	void Draw(void);

	void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);

	void SetCheck(bool ch);

	std::string m_name_;
	SDL_Texture *tex_on_;
	SDL_Texture *tex_off_;


	bool check_;
};
#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include "FastDelegate/FastDelegate.h"
#include <string>

using namespace fastdelegate;

class I_cButton : public I_cWidget
{
 public:
	 I_cButton(std::string nameid = "wdg_button");
	~I_cButton();

	void SetPos(int x, int y, int w, int h);
	void SetText(std::string txt, SDL_Color clr);
	virtual void Draw(void);
	bool IsPressed(void);
	void SetPressedState(bool press);
	std::string GetText();
	void SetTexture(SDL_Texture *tex_up, SDL_Texture *tex_dwn);
	void SetUserData(void *ptr_data);
	void *GetUserData(void);
	void SetVisible(bool visible);
	void SetEnable(bool e);
	void SetUsingFonts(bool f);
	SDL_Texture *GetTexture(void);
	void SetShowText(bool s);
    void SetTransparent(bool b);

	typedef FastDelegate1<void *> MyDelegate;
	MyDelegate OnClick;

	//void 


protected:
	void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);
	void RenderSkin(void);
	
	void createTextTexture(void);

	SDL_Texture *tex_background;
	SDL_Rect location_;
	SDL_Rect rect_text_;
	std::string txt_;
	
	SDL_Texture *tex_button_up_;
	SDL_Texture *tex_button_down_;
	SDL_Texture *tex_current_;
	SDL_Texture *tex_text_;
	bool show_txt_;

	SDL_Color txt_clr_;
	void *ptr_Data_;

	void createUIBox(void);
	std::string m_name;
	bool custom_tex_; 
	bool visible_;
    bool transparent_;
	bool usingFonts_;
	bool enabled_;



	void dummy(void *); // absolutely needed here


};
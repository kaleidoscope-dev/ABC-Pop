#pragma once
#include "anduin.h"

class I_cWidget
{
 public:
	 I_cWidget();
	virtual ~I_cWidget();

	 virtual void SetPos(int x, int y, int w, int h);
	 void SetFocus(bool f);
	 bool GetFocus(void);
	 virtual void HandleEvent(SDL_Event *event);
	 virtual void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);
	 virtual void Draw();
	 void RenderBackground(bool b);
	 bool render_bck_;



	 SDL_Texture *vertgradient(SDL_Surface * surf, SDL_Color c1, SDL_Color c2);
	 bool focus_;
	 SDL_Rect widget_rect_;
	 ANDUIN_CONTROL_TYPE type_;
	 std::string nameId_;
};
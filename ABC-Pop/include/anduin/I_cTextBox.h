#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include <string>



class I_cTextBox : public I_cWidget
{
 public:
	 I_cTextBox();
	 ~I_cTextBox();

	 void SetPos(int x, int y, int w, int h);
	 void SetText(std::string txt, SDL_Color clr);
	 void SetText(const char *format, ...);

	 std::string GetText(void);



 protected:
	void Draw(void);
	void createUIBox(void);

	void AddLetter(char ch);
	void RenderSkin(void);
	void CreateTextTexture(SDL_Color clr);
	void HandleEvent(SDL_Event *event);
	SDL_Texture *tex_background;
	SDL_Texture *tex_text_;
	SDL_Rect location_;
	SDL_Rect rect_text_;
	std::string txt_;

	SDL_Texture *tex_current_;

	std::vector<SDL_Surface*>vGlyphList;




};
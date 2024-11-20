#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include <string>


class I_cLabel : public I_cWidget
{
 public:
	 I_cLabel();
	~I_cLabel();

	void SetPos(int x, int y, int w, int h);
	void SetText(std::string txt);
	void SetText(const char *format, ...);

	std::string GetText(void);
	void Draw(void);


private:
	void RenderSkin(void);


	SDL_Texture *tex_background;
	SDL_Texture *tex_text_;
	SDL_Rect location_;
	bool custom_tex_;
	std::string txt_;
	void createUIBox(void);
	void createTextTexture(void);




};
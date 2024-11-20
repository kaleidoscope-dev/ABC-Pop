#pragma once
#include "AndUIn.h"
#include "I_cWidget.h"
#include <string>


class I_cPicture : public I_cWidget
{
 public:
	 I_cPicture();
	~I_cPicture();

	void SetPos(int x, int y, int w, int h);
	void SetTexture(SDL_Texture *tex);
	void Draw(void);
   void SetShow(bool s);


private:
	SDL_Texture *tex_background;
	SDL_Rect location_;
   bool show_;





};
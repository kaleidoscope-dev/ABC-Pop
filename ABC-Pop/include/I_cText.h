#pragma once
//#include <stdafx.h>
#include "gameapi.h"
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

#define DRAW_LETTER_UNKNOWN 0
#define DRAW_LETTER_KNOWN 1
#define DRAW_QUESTION 2
#define DRAW_EMPTY 3

class I_cText
{
public:
	I_cText();
	~I_cText();

	void Draw(void);
	void SetLetterProperties(string txt, int x, int y, int w, int h, SDL_Color clr);
	SDL_Texture *CreateLetterTex(string txt, int x, int y, SDL_Color clr);
	string GetString(void);
	void SetString(string s);
	void SetPosition(int x, int y);
	SDL_Texture *GetTextTexture(void);

    void SetShow(bool b);

    int drawType_;

private:

	int posx, posy, width, height;
	string text_string;
	void RenderLetter(SDL_Texture *tex, SDL_Rect *location);


	SDL_Texture *texLetterClr1_;
	SDL_Texture *texLetterClr2_;
	SDL_Texture *texQuestion_;
	SDL_Color clr_;
	bool drawUnknown_;
    bool show_;
};
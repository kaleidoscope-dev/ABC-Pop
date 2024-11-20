#pragma once
#include "gameapi.h"
#include "I_cText.h"



class I_cStarDroplet
{

public:
	I_cStarDroplet();
	~I_cStarDroplet();

	SDL_Rect star_rect_;

	void Init(float startx, float starty, SDL_Color clr);
	void SetLetter(string letter);
	bool Draw(void);
	void Draw_rct(void);
	//bool IsTop(void);
	bool IsClicked(int mx, int my);
	void Pop(void);
	string GetLetter(void);

	SDL_Color clr_;
	b2Body *world_body_;
	float posx_, posy_;

private:

	b2Body *CreatePhysicBody(float px, float py);
	void DrawLetter(void);

private:
	I_cText letter_;
	SDL_Texture *tex;
	bool pop_;


};









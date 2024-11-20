#pragma once
#include "gameapi.h"



class I_cAnimal
{

public:
	I_cAnimal();
	~I_cAnimal();

	SDL_Rect animal_rect_;

	void Init(float startx, float starty, GAMEAPI_ANIMAL animal);

	bool Draw(void);
	void Draw_rct(void);
	//bool IsTop(void);
	bool IsClicked(int mx, int my);
	void Pop(void);

	b2Body *world_body_;
	float posx_, posy_;


	GAMEAPI_ANIMAL GetAnimal(void);

private:

	b2Body *CreatePhysicBody(float px, float py);
	void DrawAnimal(void);

private:
	SDL_Texture *tex;
	bool pop_;
	GAMEAPI_ANIMAL animal_;


};









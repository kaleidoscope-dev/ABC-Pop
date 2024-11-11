#pragma once
#include "gameapi.h"
#include "I_cAnimate.h"
#include "I_cText.h"
//#include "I_cTile.h"



class I_cBalloon
{

 public:
	    I_cBalloon();
       ~I_cBalloon();

	   SDL_Rect balloon_rect_;

	   void Init(float startx, float starty, GAMEAPI_BALLOON_COLOR type, bool small);
	   void Init(float startx, float starty, bool small);

	   GAMEAPI_BALLOON_COLOR GetType(void);
	   void Draw(void);
	   void Draw(int x, int y);
	   void Draw_rct(void);
	   //bool IsTop(void);
	   bool IsClicked(int mx, int my);
	   void Pop(void);

	   b2Body *world_body_;

		 bool delete_;

		 bool small_;

 private:

		 void SetType(GAMEAPI_BALLOON_COLOR type);
		 b2Body *CreatePhysicBody(float px, float py);
		 void DrawLetter(void);


private:
		 I_cAnimate anima_;
		 I_cText letter_;
		 GAMEAPI_BALLOON_COLOR balloon_type_;
		 SDL_Texture *tex;
		 vector<SDL_Texture*> *ptr_vTextureList;
		 bool pop_;



};









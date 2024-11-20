#pragma once
#include "I_cText.h"

class I_cTextBar
{
 public:
		I_cTextBar();
	   ~I_cTextBar();

	   void Init(string txt, SDL_Texture *image, SDL_Texture *background);
		 void Reinit(void);
	   void SetLetter(int pos, string letter);
	   void Draw(void);

		 bool AddLetter(string letter);
		 bool ContainsLetter(string letter);
		 void Update(string letter);
		 bool CheckLevelComplete(void);
		 string GetRandomTextBarLetter(void);
		 void Reset(void);


 private:
       int posx_;
	   int posy_;
		 string txt_;
	   vector<I_cText>vLetterList;
	   I_cText letterList[12];
	   SDL_Texture *tex_background;
	   SDL_Texture *tex_animal_;
	   SDL_Rect text_rect_;
		 SDL_Rect animal_rect_;
		 SDL_Rect panel_rect_;


};
#pragma once
#include "anduin/anduin.h"
#include "gameapi.h"
#include "I_cBalloon.h"
#include "I_cLetter.h"
#include "I_cTextBar.h"
#include "I_cParallax.h"
#include "I_cLifeBar.h"
#include "I_cAnimalBar.h"
#include "I_cCollectable.h"
#include "I_cAnimal.h"
#include "anduin/I_cAndUIn.h"
#include "include/I_cStarDroplet.h"
#include <list>

class I_cLevel
{
 public:
		I_cLevel();
		~I_cLevel();

		void Draw(bool update);

		void Init(SDL_Texture *image, string str, GAMEAPI_WORLD_TYPE world, int level);
		void Reinit(void);
		void OnClick(int mx, int my);
		void Reset(void);
		void OnClick_Letter(int mx, int my);
		void CreateBalloon(void);
		//void Clear(void);
		void SetParalax(GAMEAPI_WORLD_TYPE type);
		int GetStarCount(void);
		void ResetStars(void);
		void CreateCollectableBalloon(void);
		string GetRandomTextBarLetter(void);
		int Finish(void);
        void DrawStars(void);
        void CreateStars(int x, int y);

		b2Body *GAMEAPI_AddLine_test(void);
		b2Body *GAMEAPI_AddRect_test(int x, int y, int w, int h);

		void test_draw_line(void);
		void test_draw_rect(b2Body *ptr_body);
		b2Body *body_left_wall;
		b2Body *body_right_wall;

		list<I_cBalloon*>vBalloonList;
		vector<I_cLetter*>vLetterList;
        list <I_cStarDroplet*> vStarList;

		I_cCollectable *collectable;

		SDL_Texture *texture_background_;

		I_cParallax paralax;
		
		I_cTextBar textBar;
		I_cLifeBar lifeBar;
		I_cAnimalBar animalBar;

		SDL_Rect left_rect;
		SDL_Rect right_rect;


		bool update_;  // Hack to update level because joker is the only event we don't use box2d for
		               // Call from: I_cEngine::SetUpdate


	 bool generateCollectable_;
};
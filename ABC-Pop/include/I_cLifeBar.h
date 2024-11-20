#pragma once
#include "gameapi.h"

#define MAX_LIVES 3

class I_cLifeBar
{
 public:
		I_cLifeBar();
	   ~I_cLifeBar();

	   void Init(void);
	   void AddLife(void);
	   int RemoveLife(void);
	   int GetStarCount(void);
		 void SetLives(int lives);
       void Draw();
	   void Reset(void);

		 void SetPos(int x, int y);

 private:
		uint8_t numLives_;
		int STAR_SIZE;
		int posx_;
		int posy_;

		
};
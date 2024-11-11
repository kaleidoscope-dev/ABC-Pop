#pragma once
#include "anduin/I_cPicture.h"

class I_cStars
{
 public:
			 I_cStars();
			~I_cStars();

			void Init(int num, SDL_Rect rect);
			void Init(int num, int x, int y, int w, int h);

			void OnShow(void);

			void SetStars(int num);
			bool HasStars(void);



			int num_;


			I_cPicture pic_left;
			I_cPicture pic_middle;
			I_cPicture pic_right;
};
#include "I_cStars.h"
#include "I_cAssetmanager.h"

I_cStars::I_cStars()
{
 num_ = 255;
 
}


I_cStars::~I_cStars()
{
}


void I_cStars::Init(int num, SDL_Rect rect)
{
	int left_x = rect.x - rect.w;
	int left_y = rect.y - rect.h / 2;

	int right_x = rect.x + rect.w;
	int right_y = rect.y - rect.h / 2;

	pic_left.SetPos(left_x, left_y, rect.w, rect.h);
	pic_middle.SetPos(rect.x, rect.y, rect.w, rect.h);
	pic_right.SetPos(right_x, right_y, rect.w, rect.h);


	pic_left.SetTexture(gAssetManager->GetStarGold());
	pic_middle.SetTexture(gAssetManager->GetStarGold());
	pic_right.SetTexture(gAssetManager->GetStarGold());

	num_ = num;

}

void I_cStars::Init(int num, int x, int y, int w, int h)
{


	int left_x = x - w;
  int left_y = y - h/2;

	int right_x = x + w;
	int right_y = y - h/2;

	pic_left.SetPos(left_x,left_y,w,h);
	pic_middle.SetPos(x,y,w,h);
	pic_right.SetPos(right_x, right_y, w,h);


	pic_left.SetTexture(gAssetManager->GetStarGold());
	pic_middle.SetTexture(gAssetManager->GetStarGold());
	pic_right.SetTexture(gAssetManager->GetStarGold());

	num_= num;

}


void I_cStars::SetStars(int num)
{
num_ = num;
}


bool I_cStars::HasStars(void)
{
	switch (num_)
	{
	case -1:
		return false;
	case 0:
	case 1:
	case 2:
	case 3:
		return true;

	default: return false;

	}
}


void I_cStars::OnShow(void)
{ 
	switch (num_)
	{
	 case 255:
       pic_left.SetShow(false);
       pic_middle.SetShow(false);
       pic_right.SetShow(false);
	   return;
	 case 0:
		 pic_left.SetTexture(gAssetManager->GetStarGray());
		 pic_middle.SetTexture(gAssetManager->GetStarGray());
		 pic_right.SetTexture(gAssetManager->GetStarGray());
		 break;
	 case 1:
		 pic_left.SetTexture(gAssetManager->GetStarGray());
		 pic_middle.SetTexture(gAssetManager->GetStarGold());
		 pic_right.SetTexture(gAssetManager->GetStarGray());
		 break;
		 case 2:
			 pic_left.SetTexture(gAssetManager->GetStarGold());
			 pic_middle.SetTexture(gAssetManager->GetStarGray());
			 pic_right.SetTexture(gAssetManager->GetStarGold());
       break;
	  case 3:
		  pic_left.SetTexture(gAssetManager->GetStarGold());
		  pic_middle.SetTexture(gAssetManager->GetStarGold());
		  pic_right.SetTexture(gAssetManager->GetStarGold());
			break;

		default: 
		 return;

	}


	pic_left.Draw();
	pic_middle.Draw();
	pic_right.Draw();
}

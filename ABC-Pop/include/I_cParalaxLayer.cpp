#include "I_cParalaxLayer.h"
#include "I_cAssetmanager.h"
#include "anduin/anduin.h"

I_cParalaxLayer::I_cParalaxLayer()
{
}


I_cParalaxLayer::~I_cParalaxLayer()
{
}

void I_cParalaxLayer::Init(SDL_Texture *tex)
{
 currentTexture_ = tex;

 offset_ = 0;
 SDL_QueryTexture(currentTexture_, NULL, NULL, &width_, &height_);
 
 // default rect
 rect_ = GAMEAPI_GetRect(0,0,width_,height_);


}

void I_cParalaxLayer::SetRect(SDL_Rect rct)
{
 rect_ = rct;
}


SDL_Texture *I_cParalaxLayer::GetTexture(void)
{
	return currentTexture_;
}


void I_cParalaxLayer::SetScrollSpeed(float s)
{
 scroll_speed_ = s;
}


float I_cParalaxLayer::GetSpeed(void)
{
 return scroll_speed_;
}


int I_cParalaxLayer::GetLayerWidth(void)
{
 return width_;

}

int I_cParalaxLayer::GetLayerHeight(void)
{
 return height_;
}




 float I_cParalaxLayer::GetScrollSpeed(void)
 {
  return scroll_speed_;
 }


void I_cParalaxLayer::Update(bool update)
{
 if (update)
		offset_ -= scroll_speed_;
}


int I_cParalaxLayer::GetOffset(void)
{
 return (int)offset_;
}



void I_cParalaxLayer::Reset(void)
{
 offset_ = 0;
}






void I_cParalaxLayer::Draw(void)
{
   SDL_Texture* ptr_tex = GetTexture();
   //SDL_Rect dest = { GetOffset(), rect_.y, GetLayerWidth(),GetLayerHeight() };
   //SDL_Rect dest1 = { GetLayerWidth()+GetOffset(), rect_.y, GetLayerWidth(),GetLayerHeight() };

   SDL_Rect dest = { GetOffset(), rect_.y, rect_.w, rect_.h };
   SDL_Rect dest1 = { rect_.w + GetOffset(), rect_.y, rect_.w, rect_.h };


   if (GetOffset() < -rect_.w)
       Reset();


   SDL_RenderCopy(AndUIn::renderer_, ptr_tex, NULL, &dest);
   SDL_RenderCopy(AndUIn::renderer_, ptr_tex, NULL, &dest1);

}


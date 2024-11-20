#pragma once
#include "anduin.h"
#include "I_cButton.h"
#include "FastDelegate/FastDelegate.h"
#include <string>

using namespace fastdelegate;

class I_cImageButton : public I_cButton
{
 public:
	 I_cImageButton(std::string nameid = "img_button");
	~I_cImageButton();

	void SetImage(SDL_Texture *tex, AndUIn::Orientation orientation);
	void Draw(void);



 SDL_Texture *image_;
 AndUIn::Orientation orient_;

 bool show_pic_;
 void SetShowPic(bool s);
 void AddPicture(SDL_Rect pos, SDL_Texture *tex);
 void ClearPictures(void);


 typedef struct {
	 SDL_Texture *tex;
	 SDL_Rect rect;
 }PICTURE;

 std::vector<PICTURE>vPictureList;


 PICTURE pic;
};
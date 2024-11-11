#pragma once
#include "anduin/I_cImageButton.h"



class I_cMarkerButton : public I_cImageButton
{
 public:
	      I_cMarkerButton();
	     ~I_cMarkerButton();


             void SetUpdate(bool b);
			 void Draw(void);
			 void wavefunc();


			 int x, y;
             bool update_;

};
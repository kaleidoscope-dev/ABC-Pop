#pragma once
#include "AndUIn.h"
#include "I_cTextBox.h"




class I_cPanel : public I_cTextBox
{
 public:
	 I_cPanel();
	~I_cPanel();

	//void Init(void);
	
  void Draw(void);


};
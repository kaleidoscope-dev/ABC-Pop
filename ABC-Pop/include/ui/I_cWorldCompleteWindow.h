#pragma once
#include "include/gameapi.h"
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cButton.h"
#include "anduin/I_cImageButton.h"
#include "anduin/I_cPicture.h"
#include "include/I_cLifeBar.h"


class I_cWorldCompleteWindow : public I_cWindow
{
public:
	I_cWorldCompleteWindow();
	~I_cWorldCompleteWindow();


	I_cPicture *pic_frame;
	I_cPicture *stat_frame;

	I_cImageButton *butt_continue;


	I_cButton *level_marker[6];
	I_cPicture *level_animal[6];

	I_cLifeBar star_bars[6];

	void OnContinue(void *ptr_data);

	void Init(void);
	void Draw(void);

	void Update(void);

};
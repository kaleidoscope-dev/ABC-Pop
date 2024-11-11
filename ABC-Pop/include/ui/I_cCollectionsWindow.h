#pragma once 
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "anduin/I_cImageButton.h"

class I_cCollectionsWindow: public I_cWindow
{
public:
	I_cCollectionsWindow();
	~I_cCollectionsWindow();


	void Init(void);


	I_cImageButton *btn_show_collections_;
	I_cImageButton *btn_dictionary_;
	I_cImageButton *btn_credits_;

	I_cButton *btn_return_;

	void CreateBackButton();
	void OnReturn(void* ptr_data);

	void OnShow_AnimalCollections(void *ptr_data);
	void OnShow_Dictionary(void *ptr_data);
	void OnShow_Keyboard(void *ptr_data);

	void ReinitPhase(void);


	void Draw(void);
};
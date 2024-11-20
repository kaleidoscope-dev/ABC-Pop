#pragma once 
#include "anduin/anduin.h"
#include "anduin/I_cWindow.h"
#include "I_cMarkerButton.h"
#include "include/I_cStars.h"
#include "include/gameapi.h"

class I_cLevelSelectWindow : public I_cWindow
{
 public: 
	 I_cLevelSelectWindow();
	~I_cLevelSelectWindow();

	void Init(GAMEAPI_WORLD_TYPE type);

	void SetMarkerPos(int level);
	I_cMarkerButton *GetMarkerButton(void);


	void EnableLevel(int level);
	void DisableLevelClick(int level);
	void SetStarCount(int level, int cnt);
	int currentLevel_;
	void Draw(void);
    void OnShow(void);
    void OnClose(void);

    void NextLevel(int level);
	 //void ReinitPhase(void);

	 private:
	 SDL_Texture *tex_star_num_; // nakon zavrsenog nivoa ova texture se postavlja na broj zvjedica


	 I_cButton* btn_return_;

	 void CreateBackButton();
	 void OnReturn(void* ptr_data);



     GAMEAPI_WORLD_TYPE type_;
	 I_cMarkerButton *marker_;
	 I_cStars stars[6];
     I_cPicture animal_pic[6];

	 void OnLevelSelect(void *ptr_data);
     void UpdateData(void);


};
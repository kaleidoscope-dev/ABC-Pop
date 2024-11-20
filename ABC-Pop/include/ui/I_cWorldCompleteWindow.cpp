#include "I_cWorldCompleteWindow.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"

I_cWorldCompleteWindow::I_cWorldCompleteWindow()
{
}


I_cWorldCompleteWindow::~I_cWorldCompleteWindow()
{
/*
 delete pic_frame;
 delete stat_frame;
 */
}


void I_cWorldCompleteWindow::Draw()
{
 I_cWindow::Draw();

 for (int c=0;c<6;c++)
     {
		  star_bars[c].Draw();
		 }
}




void I_cWorldCompleteWindow::Init(void)
{
	SetBackgroundTexture(gAssetManager->GetLevelBackground((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld()));  // NOTE: mora biti za na kojem smo svijetu

	pic_frame = new I_cPicture();
	pic_frame->SetTexture(gAssetManager->GetGoldFrame());
	pic_frame->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);

	stat_frame = new  I_cPicture();
	stat_frame->SetTexture(gAssetManager->GetStatFrame());
	stat_frame->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);

	AddWidget(stat_frame);
	AddWidget(pic_frame);

	int marker_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 25);
	int marker_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 5);
	int marker_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	int marker_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);
	
	
	for (int c=0;c<6;c++)
	    {


			 level_animal[c] = new I_cPicture();
			 level_animal[c]->SetTexture(gAssetManager->GetAnimal(gGameData.GetCurrentWorld(),c));  
			 level_animal[c]->SetPos(marker_x, marker_y + c * marker_h + marker_h, marker_w, marker_h);
			 AddWidget(level_animal[c]);


			 star_bars[c].Init();
			 star_bars[c].SetPos(marker_x + marker_w, (marker_y + c * marker_h + marker_h)+25);
			 star_bars[c].SetLives(gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[c].star_num);

		  }



	int height = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int contw = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 70);
	int y5 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 75);
	int x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


    int arrow_size = GAMEAPI_GetPercentage(60,height);

	butt_continue = new I_cImageButton();
	butt_continue->SetPos(x,y5, contw, height);
	butt_continue->SetText("Continue",AndUIn::White);
	butt_continue->AddPicture(GAMEAPI_GetRect(x+contw/2-arrow_size/2, y5+height/5, arrow_size, arrow_size), gAssetManager->GetArrowContinue());
	butt_continue->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
	butt_continue->SetShowPic(true);

    if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
       {
        butt_continue->SetShowText(false);
	    butt_continue->SetShowPic(true);
       }else {
              butt_continue->SetShowText(true);
	          butt_continue->SetShowPic(false);
             }


	butt_continue->OnClick.bind(this, &I_cWorldCompleteWindow::OnContinue);
	AddWidget(butt_continue);
}


void I_cWorldCompleteWindow::Update(void)
{

	for (int c = 0; c < 6; c++)
	{
		//level_marker[c] = new I_cButton();
		//level_marker[c]->SetPos(marker_x, marker_y + c * marker_h + marker_h, marker_w, marker_h);
		//level_marker[c]->SetTexture(gAssetManager->GetLevelMarkerTexture((GAMEAPI_WORLD_TYPE)GAMEAPI_current_world_), gAssetManager->GetLevelMarkerTexture((GAMEAPI_WORLD_TYPE)GAMEAPI_current_world_));
		//level_marker[c]->SetText(GAMEAPI_ToString(GAMEAPI_current_level_num_ + 1).c_str(), GAMEAPI_GetColor(255, 255, 255));
		//level_marker[c]->SetUsingFonts(true);

		//AddWidget(level_marker[c]);
		star_bars[c].SetLives(gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[c].star_num);

	}
}






void I_cWorldCompleteWindow::OnContinue(void *ptr_data)
{
	GAMEAPI_CallEvent(GAMEAPI_EVENT_WORLD_COMPLETE_CONTINUE, NULL);
}

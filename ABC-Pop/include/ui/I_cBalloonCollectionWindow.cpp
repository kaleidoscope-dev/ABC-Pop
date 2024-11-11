#include "I_cBalloonCollectionWindow.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"




I_cBalloonCollectionWindow::I_cBalloonCollectionWindow()
{
}


I_cBalloonCollectionWindow::~I_cBalloonCollectionWindow()
{
}



// NOTE: deprecated
void I_cBalloonCollectionWindow::Init(I_cAndUIn *ptr_anduin)
{
/*
 int balloon_type = 1;  // za event data
 
  selected_balloon = (I_cButton*)gAnduin->CreateWidget(this, ANDUIN_CONTROL_BUTTON);


	SDL_Rect rc_sel = { GAMEAPI_WINDOW_W / 2- GAMEAPI_BALLOON_W/2,70, GAMEAPI_BALLOON_W,GAMEAPI_BALLOON_H };

	selected_balloon->SetPos(rc_sel.x, rc_sel.y, rc_sel.w, rc_sel.h);
	selected_balloon->SetTexture(gAssetManager->vTexBalloonBlue[gGameData.current_balloon_type_][0], gAssetManager->vTexBalloonBlue[gGameData.current_balloon_type_][0]);

	
	for (int c=0;c<3;c++,balloon_type++)
	    {
		   balloons_row1[c] = (I_cButton*)gAnduin->CreateWidget(this, ANDUIN_CONTROL_BUTTON);
		   SDL_Rect rc = { 130 + c*(GAMEAPI_BALLOON_W+40) ,200, GAMEAPI_BALLOON_W,GAMEAPI_BALLOON_H };
			 
			 balloons_row1[c]->SetPos(rc.x, rc.y, rc.w, rc.h);
			 if (gGameData.unlockedBalloons[c] == true)
			    {
					 balloons_row1[c]->SetTexture(gAssetManager->vTexBalloonBlue[balloon_type][0], gAssetManager->vTexBalloonBlue[balloon_type][0]);
					}else balloons_row1[c]->SetTexture(gAssetManager->GetBalloon_Unknown(), gAssetManager->GetBalloon_Unknown());

			 // tako da mozemo prepoznati balone u OnBalloonClick
			 //GAMEAPI_EVENT_DATA *data = new GAMEAPI_EVENT_DATA;
			 //data->id = balloon_type; // GAMEAPI_BALLOON_TYPE
			 data[balloon_type].id = balloon_type;
			 balloons_row1[c]->SetUserData(&data[balloon_type]);
			 balloons_row1[c]->OnClick.bind(this, &I_cBalloonCollectionWindow::OnBalloonClick);
	    }
	 
	for (int c = 0; c < 3; c++, balloon_type++)
	{
		balloons_row2[c] = (I_cButton*)gAnduin->CreateWidget(this, ANDUIN_CONTROL_BUTTON);
		SDL_Rect rc = { 130 + c * (GAMEAPI_BALLOON_W + 40) ,400, GAMEAPI_BALLOON_W,GAMEAPI_BALLOON_H };

		balloons_row2[c]->SetPos(rc.x, rc.y, rc.w, rc.h);
		if (gGameData.unlockedBalloons[3+c] == true)
			 {
				balloons_row2[c]->SetTexture(gAssetManager->vTexBalloonBlue[balloon_type][0], gAssetManager->vTexBalloonBlue[balloon_type][0]);
			 }else balloons_row2[c]->SetTexture(gAssetManager->GetBalloon_Unknown(), gAssetManager->GetBalloon_Unknown());

		// tako da mozemo prepoznati balone u OnBalloonClick
		//GAMEAPI_EVENT_DATA *data = new GAMEAPI_EVENT_DATA;
		//data->id = balloon_type; // GAMEAPI_BALLOON_TYPE
		data[balloon_type].id = balloon_type;
		balloons_row2[c]->SetUserData(&data[balloon_type]);
		balloons_row2[c]->OnClick.bind(this, &I_cBalloonCollectionWindow::OnBalloonClick);

	}
	*/
}



void I_cBalloonCollectionWindow::Draw(void)
{

	I_cWindow::Draw();

}



void I_cBalloonCollectionWindow::OnBalloonClick(void *ptr_data)
{
/*
	GAMEAPI_EVENT_DATA *data = (GAMEAPI_EVENT_DATA*)ptr_data;

	int id = data->id;
	bool b = gGameData.unlockedBalloons[data->id];
	if (gGameData.unlockedBalloons[data->id] == true)
	   {
		  selected_balloon->SetTexture(gAssetManager->vTexBalloonBlue[data->id][0], gAssetManager->vTexBalloonBlue[data->id][0]);

			gGameData.current_balloon_type_ = (GAMEAPI_BALLOON_TYPE)data->id;
		 }

	printf("");
	*/
}

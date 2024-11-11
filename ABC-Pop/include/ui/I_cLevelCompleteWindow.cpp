#include "I_cLevelCompleteWindow.h"
#include "include/gameapi.h"
#include "include/I_cAssetmanager.h"
#include "anduin/I_cLabel.h"
#include "anduin/I_cAndUIn.h"
#include "include/I_cGameData.h"

I_cLevelCompleteWindow::I_cLevelCompleteWindow()
{
 //star_num_ = 3;
}


I_cLevelCompleteWindow::~I_cLevelCompleteWindow()
{
    if (tex_miss_) 
       SDL_DestroyTexture(tex_miss_);

    if (tex_lett_miss_) 
       SDL_DestroyTexture(tex_lett_miss_);

    if (tex_pop_) 
       SDL_DestroyTexture(tex_pop_);
}

/*
void I_cLevelCompleteWindow::SetStars(int star_num)
{
	star_num_ = star_num;
}*/



void I_cLevelCompleteWindow::Update(void)
{


	//level_marker->SetText(GAMEAPI_ToString(gGameData.GetCurrentLevel() + 1).c_str(), GAMEAPI_GetColor(255, 255, 255));
    if (tex_miss_) 
       SDL_DestroyTexture(tex_miss_);

    if (tex_lett_miss_) 
       SDL_DestroyTexture(tex_lett_miss_);

    if (tex_pop_) 
       SDL_DestroyTexture(tex_pop_);


    tex_pop_ = GAMEAPI_GetStringTexture(GAMEAPI_ToString(gGameData.balloons_pop_), AndUIn::White);
    tex_miss_ = GAMEAPI_GetStringTexture(GAMEAPI_ToString(gGameData.balloons_miss_), AndUIn::White);
    tex_lett_miss_ = GAMEAPI_GetStringTexture(GAMEAPI_ToString(gGameData.letter_miss_), AndUIn::White);


	tmp_init_stars();

	pic_animal->SetTexture(gAssetManager->GetAnimal(gGameData.GetCurrentWorld(),(GAMEAPI_ANIMAL)gGameData.GetCurrentLevel()));

	//gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[gGameData.GetCurrentLevel()].finished = true;
//	gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[GAMEAPI_current_level_num_].in_progress = false;

    if (star_count_ == 3)
       {
		if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
		    gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[gGameData.GetCurrentLevel()].animal.collected1 = true;
			else gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[gGameData.GetCurrentLevel()].animal.collected2 = true;
       }



 if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
    {
     butt_continue->SetShowText(false);
	 butt_continue->SetShowPic(true);
    }else {
           butt_continue->SetShowText(true);
	       butt_continue->SetShowPic(false);
          }
   
	
}

void I_cLevelCompleteWindow::Init(void)
{
	SetBackgroundTexture(gAssetManager->GetLevelBackground((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld()));  // NOTE: mora biti za na kojem smo svijetu

	pic_frame = new I_cPicture();
	pic_frame->SetTexture(gAssetManager->GetGoldFrame());
	pic_frame->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);

	stat_frame = new  I_cPicture();
	stat_frame->SetTexture(gAssetManager->GetStatFrame());
	stat_frame->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);

	pic_balloon = new I_cPicture();
	pic_balloon->SetTexture(gAssetManager->GetBalloon(GAMEAPI_BALLOON_COLOR_BLUE));

	pic_animal = new I_cPicture();
	pic_animal->SetTexture(gAssetManager->GetAnimal((GAMEAPI_ANIMAL)gGameData.GetCurrentLevel()));


	pic_miss = new I_cPicture();
	pic_lett_miss = new I_cPicture();




	pic_miss->SetTexture(gAssetManager->GetBalloonMiss());
	pic_lett_miss->SetTexture(gAssetManager->GetLetterMiss());


	butt_continue = new I_cImageButton();


	AddWidget(stat_frame);
	AddWidget(butt_continue);
	AddWidget(pic_frame);
	AddWidget(pic_balloon);

	AddWidget(pic_miss);
	AddWidget(pic_lett_miss);

	int marker_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
	int marker_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 12);
	int marker_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int marker_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);
	// stvori marker button, i postavi na level 1
	//level_marker = new I_cButton();
	//level_marker->SetPos(marker_x - marker_w/2, marker_y, marker_w, marker_h);
	//level_marker->SetTexture(gAssetManager->GetLevelMarkerTexture((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld()), gAssetManager->GetLevelMarkerTexture((GAMEAPI_WORLD_TYPE)gGameData.GetCurrentWorld()));
	//level_marker->SetText(GAMEAPI_ToString(gGameData.GetCurrentLevel()+1).c_str(), GAMEAPI_GetColor(255, 255, 255));
	//level_marker->SetUsingFonts(true);

	pic_animal->SetPos(marker_x - marker_w / 2, marker_y, marker_w, marker_h);

	//AddWidget(level_marker);
	AddWidget(pic_animal);


	//label_pop = new I_cTextBox();
	//label_miss = new I_cTextBox();
	//label_lett_miss = new I_cTextBox();

	int width = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 40);
	int height = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int contw = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 70);

	int y1 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 43);
	int y2 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 53);
	int y3 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 62);

	int y5 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 75);

	int x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);

    int pic_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
    int pic_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);

	pic_balloon->SetPos(x,y1,pic_w,pic_h);
	pic_miss->SetPos(x, y2, pic_w,pic_h);
	pic_lett_miss->SetPos(x, y3, pic_w,pic_h);
	


    tex_pop_ = GAMEAPI_GetStringTexture(GAMEAPI_ToString(gGameData.balloons_pop_), AndUIn::White);
    tex_miss_ = GAMEAPI_GetStringTexture(GAMEAPI_ToString(gGameData.balloons_miss_), AndUIn::White);
    tex_lett_miss_ = GAMEAPI_GetStringTexture(GAMEAPI_ToString(gGameData.letter_miss_), AndUIn::White);




//	label_pop->SetPos(x+100, y1+20, width, 60);
//	label_pop->RenderBackground(false);
//	label_pop->SetText("%d", gGameData.balloons_pop_);
////	label_pop->
//
//	label_miss->SetPos(x+100, y2, width, 60);
//	label_miss->RenderBackground(false);
//	label_miss->SetText("%d", gGameData.balloons_miss_);
//
//	label_lett_miss->SetPos(x+100, y3, width, 60);
//	label_lett_miss->RenderBackground(false);
//	label_lett_miss->SetText("%d", gGameData.letter_miss_);

	/*AddWidget(label_pop);
	AddWidget(label_miss);
	AddWidget(label_lett_miss);*/


    int arrow_size = GAMEAPI_GetPercentage(60,height);

	butt_continue->SetPos(x,y5, contw, height);
	butt_continue->SetText("Continue",AndUIn::White);
	butt_continue->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
	butt_continue->AddPicture(GAMEAPI_GetRect(x+contw/2-arrow_size/2, y5+height/5, arrow_size, arrow_size), gAssetManager->GetArrowContinue());

    if (GAMEAPI_Phase_ == GAMEAPI_PHASE_1)
       {
        butt_continue->SetShowText(false);
	    butt_continue->SetShowPic(true);
       }else {
              butt_continue->SetShowText(true);
	          butt_continue->SetShowPic(false);
             }


	butt_continue->OnClick.bind(this, &I_cLevelCompleteWindow::OnContinue);

	for (int c = 0; c < 3; c++)
	{
		pic_star[c] = new I_cPicture();
	}

	tmp_init_stars();

	int star_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
	int star_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
	int star_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
	int star_h = star_w;

	pic_star[0]->SetPos(star_x-star_w/2, star_y, star_w, star_h);   // centar
	pic_star[1]->SetPos(star_x-star_w*2, star_y - star_h/2, star_w, star_h); // ljevo
	pic_star[2]->SetPos(star_x + star_w, star_y - star_h / 2, star_w, star_h); // ljevo


	AddWidget(pic_star[0]);
	AddWidget(pic_star[1]);
	AddWidget(pic_star[2]);

}


void I_cLevelCompleteWindow::OnContinue(void *ptr_data)
{
 GAMEAPI_CallEvent(GAMEAPI_EVENT_ON_NEXT_LEVEL,NULL);
}



void I_cLevelCompleteWindow::Draw(void)
{

	I_cWindow::Draw();


    int pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 40);
	int y1 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 43);
	int y2 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 53);
	int y3 = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 62);
    int wh = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);


	SDL_Rect location = GAMEAPI_GetRect(pos_x,y1,wh,wh);
	SDL_RenderCopy(gAssetManager->GetRenderer(), tex_pop_, NULL, &location);

	location = GAMEAPI_GetRect(pos_x,y2,wh,wh);
	SDL_RenderCopy(gAssetManager->GetRenderer(), tex_miss_, NULL, &location);

	location = GAMEAPI_GetRect(pos_x,y3,wh,wh);
	SDL_RenderCopy(gAssetManager->GetRenderer(), tex_lett_miss_, NULL, &location);

}


void I_cLevelCompleteWindow::SetStarCount(int cnt)
{
 star_count_ = cnt;
}

void I_cLevelCompleteWindow::tmp_init_stars(void)
{

    switch (star_count_)
	       {
					 case 3:
						 pic_star[0]->SetTexture(gAssetManager->GetStarGold());
						 pic_star[1]->SetTexture(gAssetManager->GetStarGold());
						 pic_star[2]->SetTexture(gAssetManager->GetStarGold());
						 break;
					 
					 case 2:
						 pic_star[0]->SetTexture(gAssetManager->GetStarGray());
						 pic_star[1]->SetTexture(gAssetManager->GetStarGold());
						 pic_star[2]->SetTexture(gAssetManager->GetStarGold());
						 break;
					 case 1:
						 pic_star[0]->SetTexture(gAssetManager->GetStarGold());
						 pic_star[1]->SetTexture(gAssetManager->GetStarGray());
						 pic_star[2]->SetTexture(gAssetManager->GetStarGray());
					   break;

					 default:
						 pic_star[0]->SetTexture(gAssetManager->GetStarGray());
						 pic_star[1]->SetTexture(gAssetManager->GetStarGray());
						 pic_star[2]->SetTexture(gAssetManager->GetStarGray());
						 break;
				 }

	 


	




}

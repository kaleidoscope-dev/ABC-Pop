#include "I_cLevelSelectWindow.h"
//#include "anduin/I_cButton.h"
#include "../gameapi.h"
#include "../I_cGameData.h"
#include "../I_cAssetmanager.h"
#include "../I_cSoundBlaster.h"


I_cLevelSelectWindow::I_cLevelSelectWindow()
{
 currentLevel_ = 0;




}

// I_cPictures definirani u ovoj klasi nisu objekti. Mormo ih maknuti rucno
// jer ce ih inace ~I_cWindow pokusati izbrisati
I_cLevelSelectWindow::~I_cLevelSelectWindow()
{
 for (int c=0;c<GAMEAPI_LEVEL_COUNT;c++) 
     {
      RemoveWidget(&stars[c].pic_left);
      RemoveWidget(&stars[c].pic_middle);
      RemoveWidget(&stars[c].pic_right);
      RemoveWidget(&animal_pic[c]);
     }
}



void I_cLevelSelectWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_return_ = new I_cButton(); // back to main menu

	btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_return_->OnClick.bind(this, &I_cLevelSelectWindow::OnReturn);  // back to main menu from credits window
}



// ako postoje zavrseni nivoi, postavi te nivoe da su vidljivi i postavi 
// poziciju markera na zadnji nezavrseni nivo
void I_cLevelSelectWindow::Init(GAMEAPI_WORLD_TYPE type)
{
    type_ = type;
	SetBackgroundTexture(gAssetManager->GetLevelBackground(type));

	// stvori LEVEL_COUNT buttona na prozoru. svi buttoni su nevidljivi na pocetku
	for (int c = 0, x = 0, y = 0; c < GAMEAPI_LEVEL_COUNT; c++, x++)
	    {
		 I_cButton* btn = new I_cButton();
		 GAMEAPI_EVENT_DATA* data = new GAMEAPI_EVENT_DATA;
		 data->id = c;
		 btn->SetUserData(data);
		 btn->SetTexture(gAssetManager->GetLevelSelectButtonTexture(type), gAssetManager->GetLevelSelectButtonTexture(type));

		 if (gGameData.IsLevelFinished(type, c))
		 	 btn->SetVisible(true);
		     else btn->SetVisible(false);

		 AddWidget(btn);
	    }

	// postavi poziciju tipki na rijeku i stazu
	// 1
	int pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 19);
	int pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 18);
	int size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	int size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	GetControl(0)->SetPos(pos_x, pos_y, size_w, size_h);

	// 2
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 70);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	GetControl(1)->SetPos(pos_x, pos_y, size_w, size_h);

	// 3
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 50);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	GetControl(2)->SetPos(pos_x, pos_y, size_w, size_h);

	// 4
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 62);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	GetControl(3)->SetPos(pos_x, pos_y, size_w, size_h);

	// 5
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 75);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 70);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	GetControl(4)->SetPos(pos_x, pos_y, size_w, size_h);

	// 6
	pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 50);
	pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 87);
	size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 13);
	size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 7);

	GetControl(5)->SetPos(pos_x, pos_y, size_w, size_h);

	// stvori marker button, i postavi na level 1
	I_cMarkerButton* btn_level_marker = new I_cMarkerButton();
	SDL_Rect rc = GetControl(0)->widget_rect_;



	btn_level_marker->SetPos(rc.x, rc.y, rc.w, rc.h);
	btn_level_marker->SetTexture(gAssetManager->GetLevelMarkerTexture(type), gAssetManager->GetLevelMarkerTexture(type));
	btn_level_marker->SetText("1", GAMEAPI_GetColor(255, 255, 255));
	btn_level_marker->SetUsingFonts(true);
	AddWidget(btn_level_marker);



	// i na kraju, postavi samo prvi nivo button da je vidljiv
	I_cButton* ptr_level1 = (I_cButton*)GetControl(0);
	ptr_level1->SetVisible(true);

	CreateBackButton();

	AddWidget(btn_return_);

    marker_ = GetMarkerButton();


  for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
      {
	   SetStarCount(c, gGameData.worldData_[type].levelData[c].star_num);
       AddWidget(&stars[c].pic_left);
       AddWidget(&stars[c].pic_middle);
       AddWidget(&stars[c].pic_right);
      }


  for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
      {
       SDL_Rect rect_animal = GetControl(c)->widget_rect_;

       animal_pic[c].SetPos(rect_animal.x,rect_animal.y,rect_animal.w,rect_animal.h);
       animal_pic[c].SetTexture(gAssetManager->GetAnimal(type, c));
       AddWidget(&animal_pic[c]);
      }


   UpdateData();
}


void I_cLevelSelectWindow::Draw(void)
{
	if (!marker_)
	    marker_ = GetMarkerButton();


	I_cWindow::Draw();


}




void I_cLevelSelectWindow::OnReturn(void* ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_WORLD_SELECT;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);

	gSoundBlaster.PlayPop();
	gSoundBlaster.StopChannel(1); // stop sfx
	gSoundBlaster.StopMusic();  // stop level music
	gSoundBlaster.PlayMainMenu(); // play theme 
}






void I_cLevelSelectWindow::NextLevel(int level)
{
 SetMarkerPos(level);
 I_cButton *button_next_level = (I_cButton*)GetControl(gGameData.GetCurrentLevel());
 button_next_level->SetVisible(true);
}




void I_cLevelSelectWindow::UpdateData(void)
{
	// osposobi sve level texture to current level
	for (int c = 0; c < GAMEAPI_LEVEL_COUNT; c++)
	{
 	 //bool finished = gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[c].finished;
 	 bool finished = gGameData.worldData_[type_].levelData[c].finished;

		if (finished)
		{
         if (c == 5)
            {
             printf("");
            }
		 EnableLevel(c);
		}else {
		       DisableLevelClick(c);
			   //SetStarCount(c, gGameData.worldData_[gGameData.GetCurrentWorld()].levelData[c].star_num);
			   SetStarCount(c, gGameData.worldData_[type_].levelData[c].star_num);
			  }
	}
    

    //int cl = gGameData.GetCurrentLevel();
	//SetMarkerPos(gGameData.GetCurrentLevel());
    //EnableLevel(gGameData.GetCurrentLevel()); 


    int lvl = gGameData.GetLastFinishedLevel(this->type_);
	SetMarkerPos(lvl);
    EnableLevel(lvl); 
    //printf("");
}






void I_cLevelSelectWindow::OnShow(void)
{
    UpdateData();
    marker_->SetUpdate(false);
    I_cWindow::OnShow();
    marker_->SetUpdate(true);
    


}

void I_cLevelSelectWindow::OnClose(void)
{
 marker_->SetUpdate(false);
 I_cWindow::OnClose();
 marker_->SetUpdate(true);
}



void I_cLevelSelectWindow::EnableLevel(int level)
{

  I_cButton *level_button = (I_cButton*)GetControl(level);
  level_button->SetVisible(true);

  stars[level].pic_left.SetShow(true);
  stars[level].pic_middle.SetShow(true);
  stars[level].pic_right.SetShow(true);
  stars[level].OnShow();

  animal_pic[level].SetShow(true);
}


void I_cLevelSelectWindow::DisableLevelClick(int level)
{
  I_cButton *level_button = (I_cButton*)GetControl(level);
  level_button->SetVisible(false);
 
  stars[level].pic_left.SetShow(false);
  stars[level].pic_middle.SetShow(false);
  stars[level].pic_right.SetShow(false);
  stars[level].OnShow();

  animal_pic[level].SetShow(false);
}



// Marker pozicija i marker-anima pozicija
void I_cLevelSelectWindow::SetMarkerPos(int level)
{
    marker_ = GetMarkerButton();

    int size_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 19);
    int size_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 16);

	marker_->widget_rect_ = GetControl(level)->widget_rect_;
					
	marker_->widget_rect_.y = marker_->widget_rect_.y - size_h;
	marker_->widget_rect_.w = size_w;
	marker_->widget_rect_.h = size_h;

	SDL_Rect pic_rect = marker_->widget_rect_;
	pic_rect.x += 10;
	pic_rect.y += 15;
	pic_rect.w -= 20;
	pic_rect.h -= 45;

	marker_->ClearPictures();
	marker_->AddPicture(pic_rect, gAssetManager->GetAnimal(type_, level));
	
	// moramo ponovno stvoriti texturu, ovo je hack dok ne sredim funkcije
    // ova funkcija ce forsati novo stvaranje text texture
    marker_->SetUsingFonts(true);

  currentLevel_ = level;

}



void I_cLevelSelectWindow::SetStarCount(int level, int cnt)
{
 SDL_Rect rect_stars = GetControl(level)->widget_rect_;

 int star_size = GAMEAPI_GetPercentage(5,GAMEAPI_WINDOW_W);

 stars[level].Init(cnt,rect_stars.x+star_size, rect_stars.y+star_size*2, star_size, star_size);
}




I_cMarkerButton *I_cLevelSelectWindow::GetMarkerButton(void)
{
 return (I_cMarkerButton*)GetControl(GAMEAPI_LEVEL_COUNT);  // marker je zadnja kontrola
}





void I_cLevelSelectWindow::OnLevelSelect(void *ptr_data)
{
 
}

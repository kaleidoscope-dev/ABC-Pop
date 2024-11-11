#include "I_cAnimalCollectionWindow.h"
#include "../I_cAssetmanager.h"
#include "../I_cGameData.h"




I_cAnimalCollectionWindow::I_cAnimalCollectionWindow()
{
}


I_cAnimalCollectionWindow::~I_cAnimalCollectionWindow()
{
/*
 delete butt_next;
 delete butt_prev;
 delete pic_frame;

 for (size_t c = 0; c < this->vAnimalFrameList.size(); c++)
	  delete vAnimalFrameList[c];

 vAnimalFrameList.clear();*/

}


void I_cAnimalCollectionWindow::NextCollection(void *ptr_data)
{
	current_window_++;
	if (current_window_ > WORLD_COUNT-1)
	    current_window_ = 0;


 SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}


void I_cAnimalCollectionWindow::PrevCollection(void *ptr_data)
{
	current_window_--;
	if (current_window_ <0)
		current_window_ = WORLD_COUNT-1;


	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}


void I_cAnimalCollectionWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_return_ = new I_cButton(); // back to main menu

	btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_return_->OnClick.bind(this, &I_cAnimalCollectionWindow::OnReturn);  // back to main menu from credits window
}



void I_cAnimalCollectionWindow::Init(I_cAndUIn *ptr_anduin)
{
	int frame_size = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int gap_size_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 11);
	int gap_size_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 16);
	int bt_prevnext_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int bt_prevnext_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);

	butt_next = new I_cButton();
	butt_prev = new I_cButton();

	pic_frame = new I_cPicture();
	pic_frame->SetTexture(gAssetManager->GetGoldFrame());
	pic_frame->SetPos(0,0,GAMEAPI_WINDOW_W,GAMEAPI_WINDOW_H);



	butt_prev->SetPos(10,GAMEAPI_WINDOW_H- bt_prevnext_h -10, bt_prevnext_w, bt_prevnext_h);
	butt_prev->SetTexture(gAssetManager->GetArrowLeft(), gAssetManager->GetArrowLeft());

	butt_next->SetPos(GAMEAPI_WINDOW_W- bt_prevnext_w -20, GAMEAPI_WINDOW_H - bt_prevnext_h - 10, bt_prevnext_w, bt_prevnext_h);
	butt_next->SetTexture(gAssetManager->GetArrowRight(), gAssetManager->GetArrowRight());


	butt_next->OnClick.bind(this,&I_cAnimalCollectionWindow::NextCollection);
	butt_prev->OnClick.bind(this, &I_cAnimalCollectionWindow::PrevCollection);


	//pic_panel->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);


	CreateBackButton();


	for (int c = 0; c < 12; c++)
	{
		I_cPicture *animal_frame = new I_cPicture();
		animal_frame->SetTexture(gAssetManager->GetAnimalFrame());
		vAnimalFrameList.push_back(animal_frame);
		AddWidget(animal_frame);
	}

	AddWidget(pic_frame);
	AddWidget(butt_next);
	AddWidget(butt_prev);
	AddWidget(btn_return_);


	//int trd = (GAMEAPI_WINDOW_W / 3);
	int trd = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 30);
	int frth = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 30);

   //TODO:
	int c=0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			SDL_Rect rc = { trd*x + gap_size_x  , frth* y + gap_size_y, frame_size,frame_size };
			SDL_Rect rc1 = rc;
			rc1.x -= 10;
			rc1.y -= 10;
			rc1.w += 20;
			rc1.h += 20;

			vAnimalFrameList[c++]->SetPos(rc1.x,rc1.y, rc1.w, rc1.h);
			vRectList.push_back(rc);
		}
	}

	current_window_ = WORLD_FOREST;
	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));

	int ret = GetControlCount();

	return;

}



void I_cAnimalCollectionWindow::Draw(void)
{

	I_cWindow::Draw();


	for (int c=0;c<GAMEAPI_LEVEL_COUNT;c++)
			{
		    SDL_Texture *tex_ani = NULL;
				GAMEAPI_ANIMAL animal = gGameData.GetLevelAnimal(current_window_, c, 1);
				bool collected = gGameData.IsAnimalCollected(current_window_, c, 1);

				if (collected)
					{
						tex_ani = gAssetManager->GetAnimal(animal);
						//SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetAnimalFrame(),NULL, &rc);
						SDL_RenderCopy(gAssetManager->GetRenderer(), tex_ani, NULL, &vRectList[c]);
					}else vAnimalFrameList[c]->SetTexture(gAssetManager->GetAnimalFrameq());


				collected = gGameData.IsAnimalCollected(current_window_, c, 2);
				if (collected)
				{
					tex_ani = gAssetManager->GetAnimalGold(animal);
					//SDL_RenderCopy(gAssetManager->GetRenderer(), gAssetManager->GetAnimalFrame(),NULL, &rc);
					SDL_RenderCopy(gAssetManager->GetRenderer(), tex_ani, NULL, &vRectList[c + GAMEAPI_LEVEL_COUNT]);
				}else vAnimalFrameList[GAMEAPI_LEVEL_COUNT+ c]->SetTexture(gAssetManager->GetAnimalFrameq()); 
			}

	      

}

void I_cAnimalCollectionWindow::OnReturn(void* ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_COLLECTIONS_SELECT;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);
}




#include "I_cDictionaryWindow.h"
#include "include/gameapi.h"
#include "include/I_cAssetmanager.h"
#include "include/I_cGameData.h"
#include "anduin/anduin.h"

I_cDictionaryWindow::I_cDictionaryWindow()
{
}






void I_cDictionaryWindow::NextCollection(void *ptr_data)
{
	current_window_++;
	if (current_window_ > WORLD_COUNT - 1)
		current_window_ = 0;


	for (size_t c = 0; c < vWordList.size(); c++)
	{
		vWordList[c]->SetVisible(false);
	}


	 for (size_t c = 0; c < 6; c++)
	 {
	  //printf("%d + %d * 6 = %d\n",c,current_window_, c + current_window_ *6);
  	 vWordList[c + current_window_ * 6]->SetVisible(true);
		}



	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}


void I_cDictionaryWindow::PrevCollection(void *ptr_data)
{
	current_window_--;
	if (current_window_ < 0)
		current_window_ = WORLD_COUNT - 1;

	for (size_t c = 0; c < vWordList.size(); c++)
	{
		vWordList[c]->SetVisible(false);
	}

    // TODO: nepotrebno

	for (size_t c = 0; c < 6; c++)
	{
		//printf("%d + %d * 6 = %d\n",c,current_window_, c + current_window_ *6);
		vWordList[c + current_window_ * 6]->SetVisible(true);
	}



	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}



I_cDictionaryWindow::~I_cDictionaryWindow()
{

/*
	for (size_t c = 0; c < vWordList.size(); c++)
		delete vWordList[c];

	vWordList.clear();

/*
	delete pic_frame;
	delete pic_panel;


	delete butt_next;
	delete butt_prev;
	*/
}


void I_cDictionaryWindow::CreateBackButton()
{
	int bt_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	int bt_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);


	SDL_Rect menu_back_rect = { GAMEAPI_WINDOW_W - bt_w - 20, 10,bt_w,bt_h };

	btn_return_ = new I_cButton(); // back to main menu

	btn_return_->SetPos(menu_back_rect.x, menu_back_rect.y, menu_back_rect.w, menu_back_rect.h);
	btn_return_->SetTexture(gAssetManager->GetBackToMenu(), gAssetManager->GetBackToMenu());


	btn_return_->OnClick.bind(this, &I_cDictionaryWindow::OnReturn);  // back to main menu from credits window
}




void I_cDictionaryWindow::Init(void)
{
	butt_next = new I_cButton("btn_next");
	butt_prev = new I_cButton("btn_prev");



	tex_stat_panel = gAssetManager->GetStatFrame();
	tex_forest_frame = gAssetManager->GetGoldFrame();


	pic_frame = new I_cPicture();
	pic_panel = new I_cPicture();

	
	pic_frame->SetTexture(tex_forest_frame);
	pic_frame->SetPos(0,0,GAMEAPI_WINDOW_W,GAMEAPI_WINDOW_H);

	pic_panel->SetTexture(tex_stat_panel);

	CreateBackButton();

	butt_next->OnClick.bind(this, &I_cDictionaryWindow::NextCollection);
	butt_prev->OnClick.bind(this, &I_cDictionaryWindow::PrevCollection);

	int frame_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 90);
	int frame_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 90);
	int gap_size_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 5);
	int gap_size_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 5);



	int bt_pn_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 20);
	int bt_pn_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 10);


	butt_prev->SetPos(10, GAMEAPI_WINDOW_H - bt_pn_h - 10, bt_pn_w, bt_pn_h);
	butt_prev->SetTexture(gAssetManager->GetArrowLeft(), gAssetManager->GetArrowLeft());

	butt_next->SetPos(GAMEAPI_WINDOW_W - bt_pn_w - 20, GAMEAPI_WINDOW_H - bt_pn_h - 10, bt_pn_w, bt_pn_h);
	butt_next->SetTexture(gAssetManager->GetArrowRight(), gAssetManager->GetArrowRight());


	//pic_forest_panel->SetPos(gap_size_x * 2, gap_size_y * 2, frame_w, frame_h);
	pic_panel->SetPos(0, 0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
	



	int bt_word_w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 80);
	int bt_word_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 12);
	int bt_pos_x = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 10);
	int bt_pos_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);

	AddWidget(pic_panel);

	for (int i=0;i<WORLD_COUNT;i++)  
	    {
				for (int c = 0; c < 6; c++)
				{
					I_cImageButton *box = new I_cImageButton();
					box->SetUsingFonts(true);
					box->SetPos(bt_pos_x, bt_pos_y + bt_word_h * c , bt_word_w, bt_word_h);
					box->SetText(mAnimalStringMap[c + i * 6], GAMEAPI_GetColor(255, 255, 255));
					box->SetTexture(gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, true), gAssetManager->GetUIButton(BUTTON_COLOR_GREEN, false));
					box->SetImage(gAssetManager->GetAnimal(i, c),AndUIn::OrientationLeft);
					box->SetShowPic(true);
					box->SetShowText(true);
					box->SetVisible(false);
					AddWidget(box);

					vWordList.push_back(box);
				}
		}


  // osposobi samo prvih 6	
	for (size_t c = 0; c < 6; c++)
	{
		vWordList[c]->SetVisible(true);
	}

	


	AddWidget(pic_frame);

	AddWidget(butt_next);
	AddWidget(butt_prev);

	AddWidget(btn_return_);

	int ret = GetControlCount();

	current_window_ = WORLD_FOREST;
	

	SetBackgroundTexture(gAssetManager->GetWorldBackground((GAMEAPI_WORLD_TYPE)current_window_));
}




void I_cDictionaryWindow::Draw(void)
{
	I_cWindow::Draw();



}



void I_cDictionaryWindow::OnReturn(void* ptr_data)
{
	GAMEAPI_EVENT_DATA* edata = new GAMEAPI_EVENT_DATA;
	edata->id = GAMEAPI_UI_COLLECTIONS_SELECT;
	GAMEAPI_CallEvent(GAMEAPI_EVENT_SET_UI_STATE, edata);
}




//for (it = mymap.begin(); it != mymap.end(); ++it)
//std::cout << it->first << " => " << it->second << '\n';

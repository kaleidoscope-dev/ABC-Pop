#include "I_cParallax.h"
#include "gameapi.h"
#include "I_cAssetmanager.h"
#include "anduin/anduin.h"


I_cParallax::I_cParallax()
{
}


I_cParallax::~I_cParallax()
{
}

void I_cParallax::Init(GAMEAPI_WORLD_TYPE type)
{
	SDL_Texture **ptr_tex_world = NULL;
	ptr_tex_world = gAssetManager->GetParalaxLayer(type,0);

  I_cParalaxLayer layer01;
  I_cParalaxLayer layer02;
  I_cParalaxLayer layer03;
  I_cParalaxLayer layer04;
  I_cParalaxLayer layer05;


  layer01.Init(ptr_tex_world[0]);
  layer01.SetScrollSpeed(4.0);

	layer02.Init(ptr_tex_world[1]);
	layer02.SetScrollSpeed(2.0);



  layer03.Init(ptr_tex_world[2]);
  layer03.SetScrollSpeed(1.0);


  layer04.Init(ptr_tex_world[3]);
  layer04.SetScrollSpeed(0.5);

  // sky
  layer05.Init(ptr_tex_world[4]);
  layer05.SetScrollSpeed(0.2);


  


  int layer1_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H,25);
  int layer2_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 30);
  int layer3_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 35);
  int layer4_y = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 50);
  int layer4_h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 35);


  SDL_Rect rect_layer1 = { 0,GAMEAPI_WINDOW_H - layer1_h,GAMEAPI_WINDOW_W,layer1_h };
  SDL_Rect rect_layer2 = { 0,GAMEAPI_WINDOW_H - layer2_h,GAMEAPI_WINDOW_W,layer2_h };
  SDL_Rect rect_layer3 = { 0,GAMEAPI_WINDOW_H - layer3_h,GAMEAPI_WINDOW_W,layer3_h };
  SDL_Rect rect_layer4 = { 0,GAMEAPI_WINDOW_H - layer4_y,GAMEAPI_WINDOW_W,layer4_h };
  SDL_Rect rect_layer5 = { 0,0,GAMEAPI_WINDOW_W*2,GAMEAPI_WINDOW_H };


  layer01.SetRect(rect_layer1);
  layer02.SetRect(rect_layer2);
  layer03.SetRect(rect_layer3);
  layer04.SetRect(rect_layer4);
  layer05.SetRect(rect_layer5);


  vLayerList_.push_back(layer01);
	vLayerList_.push_back(layer02);
	vLayerList_.push_back(layer03);
  vLayerList_.push_back(layer04);
  vLayerList_.push_back(layer05);


  anima_.Init(60, 30);
  anima_.Oscillate = false;


  vOffset_.push_back(0.0);
}

float I_cParallax::GetLayerOffsetSpeed(int layer_num)
{
 return vLayerList_[layer_num].GetScrollSpeed();
}


void I_cParallax::Reset(void)
{
 for (size_t c = 0; c<vOffset_.size();c++)
      vOffset_[c] = 0;

  //vLayerList_[4].SetScrollSpeed(0.6);
}

void I_cParallax::Update(void)
{
 
}


float I_cParallax::GetFrontLayerOffset(void)
{
 return 0;
}






void I_cParallax::Draw(int layer_num, bool update)
{
	I_cParalaxLayer *layer = &vLayerList_[layer_num];
	layer->Update(update);
	layer->Draw();

	
}

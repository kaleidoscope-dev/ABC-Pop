#pragma once
#include "gameapi.h"
#include "I_cParalaxLayer.h"
#include "I_cAnimate.h"


#define LAYER_COUNT 1


class I_cParallax
{
 public:
		I_cParallax();
	   ~I_cParallax();

	    void Init(GAMEAPI_WORLD_TYPE type);
		void Update(void);
		void Draw(void);
		void Draw(int layer_num, bool update);
		float GetLayerOffsetSpeed(int layer_num);
		void Reset(void);
		float GetFrontLayerOffset(void);
		

 private:
		  std::vector <I_cParalaxLayer>vLayerList_;
		  std::vector <float>vOffset_;
		  I_cAnimate anima_;
};
#pragma once
#include <SDL.h>



class I_cParalaxLayer
{
	public: 
			I_cParalaxLayer();
		   ~I_cParalaxLayer();

    public:
			void Init(SDL_Texture *tex);
			void SetScrollSpeed(float s);
			float GetScrollSpeed(void);
			float GetSpeed(void);
			int GetLayerWidth(void);
			SDL_Texture *GetTexture(void);
			void Update(bool update);
			int GetOffset(void);
			void Reset(void);
			void SetRect(SDL_Rect rct);
			int GetLayerHeight(void);
			void Draw(void);
			SDL_Rect rect_;


    private:
			//vector<SDL_Texture *> vTexList;
         SDL_Texture *currentTexture_;
			SDL_Texture *texture1_;
         SDL_Texture* texture2_;
         //TMX_IMAGELAYER *tmx_layer_;
			int width_;
			int height_;
			int posx_;
			int posy_;
			float scroll_speed_;
			float offset_;
};


#include "AndUIn.h"

SDL_Renderer *AndUIn::renderer_ = NULL;
uint32_t AndUIn::ANDUIN_UserStartEvent = 0;



TTF_Font *AndUIn::font_ = NULL;
TTF_Font *AndUIn::font_ol_ = NULL;

int AndUIn::ANDUIN_Window_W = 0;
int AndUIn::ANDUIN_Window_H = 0;


SDL_Texture *AndUIn::label_tex_ = NULL;
SDL_Texture *AndUIn::button_up_tex_ = NULL;
SDL_Texture *AndUIn::button_down_tex_ = NULL;
SDL_Texture *AndUIn::text_box_tex_ = NULL;

std::queue<AndUIn::ANDUIN_Event*> AndUIn::qEventList;


bool AndUIn::using_textures_ = false;

SDL_Color AndUIn::Red = {255,0,0};
SDL_Color AndUIn::Green = {0,255,0};
SDL_Color AndUIn::Blue = {0,0,255};
SDL_Color AndUIn::White = { 255,255,255 };

int AndUIn::font_size_ = 18;


void AndUIn::init(SDL_Renderer * ptr_renderer, bool use_tex)
{
 AndUIn::renderer_ = ptr_renderer;
 //AndUIn::ANDUIN_UserStartEvent = SDL_RegisterEvents(EVENT_COUNT);
 AndUIn::using_textures_ = use_tex;
}





void AndUIn::ANDUIN_PushEvent(ANDUIN_EVENT_TYPE type, void *ptr_data)
{
 AndUIn::ANDUIN_Event *and_ev = new AndUIn::ANDUIN_Event;
 and_ev->type = type;
 and_ev->ptr_data = ptr_data;
 qEventList.push(and_ev);
}


int AndUIn::ANDUIN_PollEvent(AndUIn::ANDUIN_Event *event)
{
	if (qEventList.size() > 0)
	{
		AndUIn::ANDUIN_Event *popEvent = qEventList.front();
	    event->type = popEvent->type;
		
		switch (event->type)
		{
	     case AndUIn::EVENT_ON_CLICK:
	      event->type = popEvent->type;
		  event->ptr_data = popEvent->ptr_data;
		  break;

		 default:
		  break;

	    }

		delete popEvent;    
		qEventList.pop();
		return 1;
	}

	return 0;
}

int AndUIn::GetPercentage(int num, int perc)
{
	int result = num * perc / 100;
	return result;
}


SDL_Rect AndUIn::GetRect(int x, int y, int w, int h)
{
 SDL_Rect rect = {x,y,w,h};
 return rect;
}

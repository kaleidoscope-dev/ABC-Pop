#pragma once




#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <queue>




typedef enum ANDUIN_Control_Type
{
	ANDUIN_CONTROL_TEXTBOX,
	ANDUIN_CONTROL_BUTTON,
	ANDUIN_CONTROL_CHECK_BUTTON,
	ANDUIN_CONTROL_IMAGE_BUTTON,
	ANDUIN_CONTROL_LABEL,
	ANDUIN_CONTROL_PICTURE,
	ANDUIN_CONTROL_INPUTBOX,
	ANDUIN_CONTROL_KEYBOARD,
	ANDUIN_CONTROL_MAX,
}ANDUIN_CONTROL_TYPE;


namespace AndUIn
{
 typedef enum ANDUIN_Event_Type
 {
  EVENT_NO_EVENT = 0,
  EVENT_TEXTBOX_END_INPUT,
  EVENT_BUTTON_DOWN,
  EVENT_BUTTON_UP,
  EVENT_KEY_DOWN,
  EVENT_ON_CLICK,
  EVENT_COUNT,
 }ANDUIN_EVENT_TYPE;


 typedef struct ANDUIN_Event
 {
  ANDUIN_EVENT_TYPE type;
  void *ptr_data;
 }ANDUIN_Event;


 void init(SDL_Renderer *ptr_renderer, bool use_tex);
 void ANDUIN_PushEvent(ANDUIN_EVENT_TYPE type, void *ptr_data);
 int ANDUIN_PollEvent(ANDUIN_Event *event);
 
int GetPercentage(int num, int perc);
SDL_Rect GetRect(int x, int y, int w, int h);


 extern SDL_Renderer *renderer_;
 extern uint32_t ANDUIN_UserStartEvent;

 extern bool using_textures_;

 
 extern int ANDUIN_Window_W;
 extern int ANDUIN_Window_H;

 extern SDL_Color Red;
 extern SDL_Color Green;
 extern SDL_Color Blue;
 extern SDL_Color White;

 enum Orientation{
	     OrientationLeft,
			 OrientationMiddle,
			 OrientationRight,
			};


 extern TTF_Font *font_;
 extern TTF_Font *font_ol_;

 extern int font_size_;

 extern std::queue<ANDUIN_Event*>qEventList;


 extern SDL_Texture *label_tex_;
 extern SDL_Texture *button_up_tex_;
 extern SDL_Texture *button_down_tex_;
 extern SDL_Texture *text_box_tex_;

}

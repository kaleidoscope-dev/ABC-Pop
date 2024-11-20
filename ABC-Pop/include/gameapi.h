
#pragma once
#include <queue>
#include <map>
#include <fstream>
#include <iostream>
#include "rnd/randomc.h"
#include <Box2D\Box2D.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "gamedef.h"


using namespace std;



extern int GAMEAPI_Player_Lives;
extern bool GAMEAPI_Debug_Draw_Surface;
extern int GAMEAPI_time_remaining;
extern int GAMEAPI_coins;


extern int GAMEAPI_WINDOW_W;
extern int GAMEAPI_WINDOW_H;


extern int GAMEAPI_BALLOON_W;   // 60  
extern int GAMEAPI_BALLOON_H;   // 90 

extern int GAMEAPI_BALLOON_SMALL_W;   // 60   
extern int GAMEAPI_BALLOON_SMALL_H;   // 90 

extern int GAMEAPI_ANIMAL_FRAME;
extern int GAMEAPI_COLLECTABLE_CHANCE;

extern int GAMEAPI_LETTER_W;   // 35
extern int GAMEAPI_LETTER_H;   // 35  

extern int GAMEAPI_ANIMAL_W;
extern int GAMEAPI_ANIMAL_H;

// prime game phase
extern int GAMEAPI_Phase_;


// box2d
const float GAMEAPI_M2P = 10;
const float GAMEAPI_P2M = 1 / GAMEAPI_M2P;

const float GAMEAPI_BodyVelocity = 8.0;
const float GAMEAPI_PlayerBodyVelocity = 1.0;



extern b2World *GAMEAPI_world_up;
extern b2World *GAMEAPI_world_down;

// Game Globals
extern uint32_t GAMEAPI_score;

extern uint32_t GAMEAPI_UserStartEvent;

extern int GAMEAPI_VersionPrime;
extern int GAMEAPI_VersionaMajor;
extern int GAMEAPI_VersionMinor;
extern int GAMEAPI_VersionBuild;
extern SDL_Texture *GAMEAPI_TextureVersionText;

extern std::string GAMEAPI_VersionString;

extern std::vector<std::string>GAMEAPI_vArtistStringList;
extern std::vector<std::string>GAMEAPI_vCreditsStringList;
extern std::vector<std::string>GAMEAPI_vWinnerStringList;


extern CRandomMersenne *rm;

// used by SDL_Mixer
typedef enum GAMEAPI_Channel
{
 CHANNEL_SFX = 0,
 CHANNEL_BACKGROUND = 1,
 CHANNEL_MUSIC = 2,
}GAMEAPI_CHANNEL;


typedef enum GAMEAPI_Button_Color
{
 BUTTON_COLOR_GREEN,
 BUTTON_COLOR_YELLOW,
 BUTTON_COLOR_BLUE,
 BUTTON_COLOR_RED,
}GAMEAPI_BUTTON_COLOR;





typedef struct GAMEAPI_Event
{
	GAMEAPI_EVENT_TYPE type;
	void *ptr_data;
	uint32_t idata;
}GAMEAPI_EVENT;


typedef struct GAMEAPI_EventData
{
 uint32_t id;
}GAMEAPI_EVENT_DATA;



typedef struct GAMEAPI_LevelData
{
 struct {
			GAMEAPI_ANIMAL animal1;
			GAMEAPI_ANIMAL animal2;
			bool collected1;
			bool collected2;
		}animal;


 bool finished;
 uint8_t star_num;
}GAMEAPI_LEVEL_DATA;

typedef struct GAMEAPI_WorldData
{
 uint8_t world;
 bool finished;
 bool in_progress;
 GAMEAPI_LEVEL_DATA levelData[GAMEAPI_LEVEL_COUNT];
}GAMEAPI_WORLD_DATA;



extern void GAMEAPI_Init(void);
extern int GAMEAPI_ToInt(string s);
extern float GAMEAPI_ToFloat(string s);
extern double GAMEAPI_ToDouble(string s);
extern uint32_t GAMEAPI_ToUint32(string s);

// TODO: testirati ove koverzije
extern string GAMEAPI_ToString(int n);



extern void GAMEAPI_CallEvent(GAMEAPI_EVENT_TYPE type, void *ptr_data);



extern int GAMEAPI_PollEvent(GAMEAPI_EVENT *event);

extern float GAMEAPI_Pix2Meter(float p);
extern float GAMEAPI_Met2Pixel(float m);


extern int GAMEAPI_decode_unsigned32(uint8_t * data, uint32_t * value);
extern int GAMEAPI_encode_unsigned32(uint8_t * data, uint32_t value);


extern SDL_Color GAMEAPI_GetColor(uint8_t r, uint8_t g, uint8_t b);
extern SDL_Rect GAMEAPI_GetRect(int x, int y, int w, int h);

extern int GAMEAPI_GetPercentage(int num, int perc);

extern int GAMEAPI_GetRandom(int a, int b);

extern SDL_Texture *GAMEAPI_GetTextTexture(string text);

extern std::queue<GAMEAPI_EVENT> qEventList;
extern std::map<int, string>mAnimalStringMap;


extern SDL_Texture *GAMEAPI_GetStringTexture(string txt, SDL_Color clr);



extern string GAMEAPI_printf(const char* format, ...);

extern void GAMEAPI_InitVersion(void);


extern void GAMEAPI_textOut(int x, int y, SDL_Color clr, const char* format, ...);


#include "gameapi.h"
#include "SDL2_gfxPrimitives.h"
#include "I_cAssetmanager.h"
#include "anduin/anduin.h"



int GAMEAPI_ANIMAL_FRAME = 100;


int GAMEAPI_BALLOON_W = 60;
int GAMEAPI_BALLOON_H = 90;

int GAMEAPI_BALLOON_SMALL_W = 40;
int GAMEAPI_BALLOON_SMALL_H = 60;


int GAMEAPI_LETTER_W = 35;   
int GAMEAPI_LETTER_H = 35;   

int GAMEAPI_ANIMAL_W = 80;
int GAMEAPI_ANIMAL_H = 80;

std::queue<GAMEAPI_EVENT> qEventList;
std::map<int, string> mAnimalStringMap;



int GAMEAPI_VersionPrime = 1;
int GAMEAPI_VersionaMajor = 0;
int GAMEAPI_VersionMinor = 1;
int GAMEAPI_VersionBuild = 0;

SDL_Texture *GAMEAPI_TextureVersionText = NULL;
std::string GAMEAPI_VersionString = "ver.Empty";
uint32_t GAMEAPI_UserStartEvent = 0;

CRandomMersenne *rm = NULL;

bool GAMEAPI_Debug_Draw_Surface = true;


int GAMEAPI_Phase_ = GAMEAPI_PHASE_1;


std::vector<std::string>GAMEAPI_vArtistStringList;
std::vector<std::string>GAMEAPI_vCreditsStringList;
std::vector<std::string>GAMEAPI_vWinnerStringList;



void GAMEAPI_Init(void)
{

	GAMEAPI_UserStartEvent = SDL_RegisterEvents(GAMEAPI_EVENT_MAX_EVENTS);

	GAMEAPI_BALLOON_W = GAMEAPI_GetPercentage(AndUIn::ANDUIN_Window_W, 25);
	GAMEAPI_BALLOON_H = GAMEAPI_GetPercentage(AndUIn::ANDUIN_Window_H, 20);

	GAMEAPI_BALLOON_SMALL_W = GAMEAPI_GetPercentage(GAMEAPI_BALLOON_W, 70);
	GAMEAPI_BALLOON_SMALL_H = GAMEAPI_GetPercentage(GAMEAPI_BALLOON_H, 70);

	
	GAMEAPI_LETTER_W = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W, 15);
	GAMEAPI_LETTER_H = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_H, 15);

	string str1 = "  Animal Characters Art and Design by: ";
	string str2 = "                brgfx                  ";
	string str3 = "       https ://www.freepik.com/       ";
	string str4 = "                                       ";
	string str5 = "Music Tracks : Wonders, Dark, Adventure";
	string str6 = "  Afternoon and Eternity are provided  ";
    string str7 = "     by the Gravity Sound Studio       ";
    string str8 = "   https ://www.gravitysound.studio/   ";
	string str9 = "      under CC BY 4.0 License          ";
	string str10 = "                                       ";
	string str11 = "Winner Window Track Under CC0 License,";
    string str12 = "         By Juhani Junkala            ";



   GAMEAPI_vArtistStringList.push_back(str1);
   GAMEAPI_vArtistStringList.push_back(str2);
   GAMEAPI_vArtistStringList.push_back(str3);
   GAMEAPI_vArtistStringList.push_back(str4);
   GAMEAPI_vArtistStringList.push_back(str5);
   GAMEAPI_vArtistStringList.push_back(str6);
   GAMEAPI_vArtistStringList.push_back(str7);
   GAMEAPI_vArtistStringList.push_back(str8);
   GAMEAPI_vArtistStringList.push_back(str9);
   GAMEAPI_vArtistStringList.push_back(str10);
   GAMEAPI_vArtistStringList.push_back(str11);
   GAMEAPI_vArtistStringList.push_back(str12);


   str1 = "       Design and Programming:         ";
   str2 = "                SIM47                  ";
   str3 = "          Kaleidoscope ltd.            ";


   GAMEAPI_vCreditsStringList.push_back(str1);
   GAMEAPI_vCreditsStringList.push_back(str2);
   GAMEAPI_vCreditsStringList.push_back(str3);


   str1 = "          Congratulations              ";
   str2 = "        On Finishing ABC-Pop!          ";
   str3 = "                                       ";
   str4 = " I hope you had fun playing my game    ";
   str5 = "    and hopefully learn some letters,  ";
   str6 = "          words and animals.           ";
   str7 = "You can always reset your game back to ";
   str8 = "     beginning in the options menu.    ";
   str9 = "       Thank you for playing!          ";


   
   GAMEAPI_vWinnerStringList.push_back(str1);
   GAMEAPI_vWinnerStringList.push_back(str2);
   GAMEAPI_vWinnerStringList.push_back(str3);
   GAMEAPI_vWinnerStringList.push_back(str4);
   GAMEAPI_vWinnerStringList.push_back(str5);
   GAMEAPI_vWinnerStringList.push_back(str6);
   GAMEAPI_vWinnerStringList.push_back(str7);
   GAMEAPI_vWinnerStringList.push_back(str8);
   GAMEAPI_vWinnerStringList.push_back(str9);

}




int GAMEAPI_ToInt(string s)
{


	int r = atoi(s.c_str());
	return r;
}


// DEPRECATED
float GAMEAPI_ToFloat(string s)
{
  
	return 0;
}


// DEPRECATED
double GAMEAPI_ToDouble(string s)
{
	return 0;
}



uint32_t GAMEAPI_ToUint32(string s)
{
	uint32_t r = atol(s.c_str());
	return r;
}


string GAMEAPI_ToString(int n)
{
	char *ch = new char[128];
	sprintf(ch, "%d", n);      // NOTE: snprintf
	string s(ch);
	delete[]ch;
	return s;
}




void GAMEAPI_CallEvent(GAMEAPI_EVENT_TYPE type, void *ptr_data)
{
 GAMEAPI_EVENT gevent;
 gevent.type = type;
 gevent.ptr_data = ptr_data;
 

 SDL_Event event;
 SDL_memset(&event, 0, sizeof(event));
 event.type = GAMEAPI_UserStartEvent;
 event.user.code = type;
 event.user.data1 = ptr_data;
 event.user.data2 = 0;
 SDL_PushEvent(&event);


}




float GAMEAPI_Pix2Meter(float p)
{
	return p * GAMEAPI_P2M;
}


float GAMEAPI_Met2Pixel(float m)
{
	return m * GAMEAPI_M2P;
}



int GAMEAPI_decode_unsigned32(uint8_t * data, uint32_t * value)
{
	if (value) {
		*value = ((uint32_t)((((uint32_t)data[0]) << 24) & 0xff000000));
		*value |= ((uint32_t)((((uint32_t)data[1]) << 16) & 0x00ff0000));
		*value |= ((uint32_t)((((uint32_t)data[2]) << 8) & 0x0000ff00));
		*value |= ((uint32_t)(((uint32_t)data[3]) & 0x000000ff));
	}

	return 4;
}


int GAMEAPI_encode_unsigned32(uint8_t * data, uint32_t value)
{
	data[0] = (uint8_t)((value & 0xff000000) >> 24);
	data[1] = (uint8_t)((value & 0x00ff0000) >> 16);
	data[2] = (uint8_t)((value & 0x0000ff00) >> 8);
	data[3] = (uint8_t)(value & 0x000000ff);

	return 4;
}

SDL_Rect GAMEAPI_GetRect(int x, int y, int w, int h)
{
 SDL_Rect rect = {x,y,w,h};
 return rect;
}



int GAMEAPI_GetPercentage(int num, int perc)
{
	int result = num * perc / 100;
	return result;
}


SDL_Color GAMEAPI_GetColor(uint8_t r, uint8_t g, uint8_t b)
{
 SDL_Color clr = {r,g,b,0};
 return clr;
}



// DEPRECATED
SDL_Texture *GAMEAPI_GetTextTexture(string text)
{
/*
	if (text.empty())
		return NULL;

	SDL_Color white = { 0xFF, 0xFF, 0xFF };
	SDL_Color black = { 0x00, 0x00, 0x00 };

	SDL_Surface *bg_surface = TTF_RenderText_Blended(gAssetManager->GetFontOutline(), text.c_str(), black);
	SDL_Surface *fg_surface = TTF_RenderText_Blended(gAssetManager->GetFont(), text.c_str(), white);
	SDL_Rect rect = { 2, 2, fg_surface->w, fg_surface->h };

	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
	SDL_FreeSurface(fg_surface);



	SDL_Texture *tex = SDL_CreateTextureFromSurface(gAssetManager->GetRenderer(), surface);

	SDL_FreeSurface(bg_surface);

	return tex;
	*/

	return 0;
}



int GAMEAPI_GetRandom(int a, int b)
{
	return rm->IRandom(a,b);
}






SDL_Texture *GAMEAPI_GetStringTexture(string txt, SDL_Color clr)
{
 if (!txt.size())
     return NULL;


	SDL_Color white = { 0xFF, 0xFF, 0xFF };
	SDL_Color black = { 0x00, 0x00, 0x00 };



	SDL_Surface *bg_surface = TTF_RenderText_Blended(gAssetManager->GetFontOutline(), txt.c_str(), black);
	SDL_Surface *fg_surface = TTF_RenderText_Blended(gAssetManager->GetFont(), txt.c_str(), clr);
	SDL_Rect rect = { 2, 2, fg_surface->w, fg_surface->h };


	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
	//SDL_FreeSurface(fg_surface);


   SDL_Texture *ret = SDL_CreateTextureFromSurface(gAssetManager->GetRenderer(), bg_surface);

	SDL_FreeSurface(bg_surface);
	SDL_FreeSurface(fg_surface);

	return ret;
}



string GAMEAPI_printf(const char* format, ...)
{
	char out[256];
	va_list arglist;

	va_start(arglist, format);
#ifdef __ANDROID__
	vsprintf(out, format, arglist);
#else
	vsprintf_s(out, format, arglist);
#endif
	va_end(arglist);

	std::string s = out;
	return s;

}


void GAMEAPI_textOut(int x, int y, SDL_Color clr, const char* format, ...)
{
	char out[256];
	va_list arglist;

	va_start(arglist, format);
#ifdef __ANDROID__
	vsprintf(out, format, arglist);
#else
	vsprintf_s(out, format, arglist);
#endif
	va_end(arglist);

	std::string s = out;
 
 //stringRGBA(
}



void GAMEAPI_InitVersion(void)
{
 std::string path;
 char verbuf[64];

#if GAMEAPI_RELEASE
 GAMEAPI_TextureVersionText = GAMEAPI_GetStringTexture(GAMEAPI_GAME_VERSION,GAMEAPI_GetColor(255,255,255));
#else 


#if __ANDROID__
	path = "ver.txt";


    SDL_RWops* rw = SDL_RWFromFile("ver.txt", "r");
    if (rw == NULL) return;

    Sint64 res_size = SDL_RWsize(rw);
    char* res = new char[res_size+1];
    SDL_RWread(rw, res, 1, res_size);

    SDL_RWclose(rw);

	sscanf(res, "%d.%d.%d.%d", &GAMEAPI_VersionPrime, &GAMEAPI_VersionaMajor, &GAMEAPI_VersionMinor, &GAMEAPI_VersionBuild);
	GAMEAPI_VersionString = GAMEAPI_printf("%d.%d.%d.%d", GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);

    GAMEAPI_VersionMinor = 6;
	GAMEAPI_VersionBuild++;

	char *ch = new char[32];
	sprintf(ch,"%d.%d.%d.%d",GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);

	rw = SDL_RWFromFile("ver.txt", "w");

	int write_size = SDL_RWwrite(rw, ch, 1, strlen(ch));

	SDL_RWclose(rw);

	delete []res;
	delete []ch;

	sprintf(verbuf,"A-%d.%d.%d.%d - Core",GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);

   


#else
	path = "ver.txt";
    

	// verzija
	FILE* f = NULL;
	f = fopen(path.c_str(), "r");
	if (f)
	{
		fscanf(f, "%d.%d.%d.%d", &GAMEAPI_VersionPrime, &GAMEAPI_VersionaMajor, &GAMEAPI_VersionMinor, &GAMEAPI_VersionBuild);
		GAMEAPI_VersionString = GAMEAPI_printf("%d.%d.%d.%d", GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);
		fclose(f);
	}else {
		   f = fopen(path.c_str(), "w");
		   if (f)
		      {
			   fprintf(f,"%d.%d.%d.%d", GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);
			   GAMEAPI_VersionString = GAMEAPI_printf("%d.%d.%d.%d", GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);
			   fclose(f);
		      }
	      }

	 // update
     GAMEAPI_VersionMinor = 8;
	 GAMEAPI_VersionBuild++;
	 f = fopen(path.c_str(), "w");
	 if (f)
	    {
		 fprintf(f, "%d.%d.%d.%d", GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);
		 fclose(f);
		}

        sprintf(verbuf,"W-%d.%d.%d.%d - Release",GAMEAPI_VersionPrime, GAMEAPI_VersionaMajor, GAMEAPI_VersionMinor, GAMEAPI_VersionBuild);

#endif // android

 GAMEAPI_TextureVersionText = GAMEAPI_GetStringTexture(verbuf,GAMEAPI_GetColor(255,255,255));

 #endif // Release
}





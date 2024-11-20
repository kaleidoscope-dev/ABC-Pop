#include "gameapi.h"
#include "I_cAssetManager.h"
#include "I_cLog.h"
#include <SDL_image.h>



I_cAssetManager *gAssetManager = 0;


I_cAssetManager::I_cAssetManager()
{
	game_font_ = NULL;
	texture_green_panel_ = NULL;
	texture_blue_panel_ = NULL;
	texture_yellow_panel_ = NULL;
	texture_red_panel_ = NULL;
	tex_ui_panel_back_ = NULL;

	tex_ui_story_panel_ = NULL;


	tex_hud_blue_rect_ = NULL;
	tex_hud_green_rect_ = NULL;
	tex_hud_orange_rect_ = NULL;
	tex_hud_pink_rect_ = NULL;
	tex_hud_purple_rect_ = NULL;
	tex_hud_red_rect_ = NULL;
	tex_hud_yellow_rect_ = NULL;




	sound_pop = NULL;


	ptr_renderer_ = NULL;
	//vector<GLuint>vTileGUIDList;
	game_font_outline_ = NULL;
	game_font_ = NULL;


}


I_cAssetManager::~I_cAssetManager()
{


 for (size_t c = 0; c < vTexBalloonBlue.size(); c++)
	 SDL_DestroyTexture(vTexBalloonBlue[c]);

 for (size_t c = 0; c < vTexBalloonBlue.size(); c++)
	 SDL_DestroyTexture(vTexBalloonRed[c]);

 for (size_t c = 0; c < vTexBalloonBlue.size(); c++)
	 SDL_DestroyTexture (vTexBalloonYellow[c]);

 for (size_t c = 0; c < vTexBalloonBlue.size(); c++)
	 SDL_DestroyTexture (vTexBalloonOrange[c]);

 for (size_t c = 0; c < vTexBalloonBlue.size(); c++)
	 SDL_DestroyTexture (vTexBalloonPink[c]);

 for (size_t c = 0; c < vTexBalloonBlue.size(); c++)
	 SDL_DestroyTexture (vTexBalloonPurple[c]);


 vTexBalloonOrange.clear();
 vTexBalloonGreen.clear();
 vTexBalloonPink.clear();
 vTexBalloonPurple.clear();
 vTexBalloonRed.clear();
 vTexBalloonYellow.clear();

 for (size_t c = 0; c < vTextureList.size(); c++)
	 SDL_DestroyTexture (vTextureList[c]);

 vTextureList.clear();

 for (int c=0;c<5;c++)
     {
	 SDL_DestroyTexture (texture_level_background[c]);
	 SDL_DestroyTexture (tex_forest_paralax[c]);
	 SDL_DestroyTexture (tex_winter_paralax[c]);
	 SDL_DestroyTexture (tex_desert_paralax[c]);
	 SDL_DestroyTexture (tex_grave_paralax[c]);
	 SDL_DestroyTexture (tex_candy_paralax[c]);
	 SDL_DestroyTexture (texture_world_collections[c]);
	
      texture_level_background[c] = NULL; 
	  tex_forest_paralax[c] = NULL;
	  tex_winter_paralax[c] = NULL;
	  tex_desert_paralax[c] = NULL;
	  tex_grave_paralax[c] = NULL;
	  tex_candy_paralax[c] = NULL;
	  texture_world_collections[c] = NULL;
     }



	 Mix_FreeChunk(sound_pop);
	 Mix_FreeChunk(sound_letter_correct_hit);
	 Mix_FreeChunk(sound_letter_miss);

	 Mix_FreeChunk(sound_forest_bck);
	 Mix_FreeChunk(sound_winter_bck);
	 Mix_FreeChunk(sound_grave_bck);

 Mix_FreeMusic (sound_main_menu);
 Mix_FreeMusic (sound_forest_music);
 Mix_FreeMusic (sound_winter_music);
 Mix_FreeMusic (sound_grave_music);
 Mix_FreeMusic (sound_desert_music);
 Mix_FreeMusic (sound_candy_music);

 
}


void I_cAssetManager::Init(SDL_Renderer *rend)
{
 ptr_renderer_ = rend;
}






GAMEAPI_ERROR I_cAssetManager::LoadAssets(void)
{
	GAMEAPI_ERROR err = GAMEAPI_OK;
	


	tex_todo = Load(GAMEAPI_TEX_TODO);


	tex_btn_forest_select_ = Load(GAMEAPI_TEX_BTN_FOREST_SELECT);
	tex_btn_winter_select_ = Load(GAMEAPI_TEX_BTN_WINTER_SELECT);
	tex_btn_desert_select_ = Load(GAMEAPI_TEX_BTN_DESERT_SELECT);
	tex_btn_grave_select_ = Load(GAMEAPI_TEX_BTN_GRAVEYARD_SELECT);
	tex_btn_candy_select_ = Load(GAMEAPI_TEX_BTN_CANDYLAND_SELECT);

	vTextureList.push_back(tex_btn_forest_select_);
	vTextureList.push_back(tex_btn_winter_select_);
	vTextureList.push_back(tex_btn_desert_select_);
	vTextureList.push_back(tex_btn_grave_select_);
	vTextureList.push_back(tex_btn_candy_select_);


	tex_btn_forest_level_ = Load(GAMEAPI_TEX_BTN_FOREST_LEVEL);
	tex_btn_winter_level_ = Load(GAMEAPI_TEX_BTN_WINTER_LEVEL);
	tex_btn_desert_level_ = Load(GAMEAPI_TEX_BTN_DESERT_LEVEL);
	tex_btn_grave_level_ = Load(GAMEAPI_TEX_BTN_GRAVEYARD_LEVEL);
	tex_btn_candy_level_ = Load(GAMEAPI_TEX_BTN_CANDYLAND_LEVEL);

	vTextureList.push_back(tex_btn_forest_level_);
	vTextureList.push_back(tex_btn_winter_level_);
	vTextureList.push_back(tex_btn_desert_level_);
	vTextureList.push_back(tex_btn_grave_level_);
	vTextureList.push_back(tex_btn_candy_level_);


	tex_balloon_unknow = Load(GAMEAPI_TEX_BALLOON_UNKNOWN);

	vTextureList.push_back(tex_balloon_unknow);

	LoadBlue();
	LoadGreen();
	LoadOrange();
	LoadPurple();
	LoadPink();
	LoadRed();
	LoadYellow();


	texture_life_ = Load(GAMEAPI_TEX_LIFE);
	vTextureList.push_back(texture_life_);


 	  texture_level_background[0] = Load(GAMEAPI_TEX_WORLD_FOREST);
		texture_level_background[1] = Load(GAMEAPI_TEX_WORLD_WINTER);
		texture_level_background[2] = Load(GAMEAPI_TEX_WORLD_DESERT);
		texture_level_background[3] = Load(GAMEAPI_TEX_WORLD_GRAVEYARD);
		texture_level_background[4] = Load(GAMEAPI_TEX_WORLD_CANDYLAND);


	texture_world_background[0] = Load(GAMEAPI_TEX_LEVEL1_BACK);
	texture_world_background[1] = Load(GAMEAPI_TEX_LEVEL2_BACK);
	texture_world_background[2] = Load(GAMEAPI_TEX_LEVEL3_BACK);
	texture_world_background[3] = Load(GAMEAPI_TEX_LEVEL4_BACK);
	texture_world_background[4] = Load(GAMEAPI_TEX_LEVEL5_BACK);



    tex_star_gold_ = Load(GAMEAPI_TEX_STAR);
	tex_star_gray_ = Load(GAMEAPI_TEX_STAR_GRAY);

	vTextureList.push_back(tex_star_gold_);
	vTextureList.push_back(tex_star_gray_);


	//LoadAnimals(void);


	
	tex_forest_paralax[0] = Load(GAMEAPI_TEX_FOREST_PARALAX1);
	tex_forest_paralax[1] = Load(GAMEAPI_TEX_FOREST_PARALAX2);
	tex_forest_paralax[2] = Load(GAMEAPI_TEX_FOREST_PARALAX3);
	tex_forest_paralax[3] = Load(GAMEAPI_TEX_FOREST_PARALAX4);
	tex_forest_paralax[4] = Load(GAMEAPI_TEX_FOREST_PARALAX5);

	tex_winter_paralax[0] = Load(GAMEAPI_TEX_WINTER_PARALAX1);
	tex_winter_paralax[1] = Load(GAMEAPI_TEX_WINTER_PARALAX2);
	tex_winter_paralax[2] = Load(GAMEAPI_TEX_WINTER_PARALAX3);
	tex_winter_paralax[3] = Load(GAMEAPI_TEX_WINTER_PARALAX4);
	tex_winter_paralax[4] = Load(GAMEAPI_TEX_WINTER_PARALAX5);

	tex_desert_paralax[0] = Load(GAMEAPI_TEX_DESERT_PARALAX1);
	tex_desert_paralax[1] = Load(GAMEAPI_TEX_DESERT_PARALAX2);
	tex_desert_paralax[2] = Load(GAMEAPI_TEX_DESERT_PARALAX3);
	tex_desert_paralax[3] = Load(GAMEAPI_TEX_DESERT_PARALAX4);
	tex_desert_paralax[4] = Load(GAMEAPI_TEX_DESERT_PARALAX5);

	tex_grave_paralax[0] = Load(GAMEAPI_TEX_GRAVE_PARALAX1);
	tex_grave_paralax[1] = Load(GAMEAPI_TEX_GRAVE_PARALAX2);
	tex_grave_paralax[2] = Load(GAMEAPI_TEX_GRAVE_PARALAX3);
	tex_grave_paralax[3] = Load(GAMEAPI_TEX_GRAVE_PARALAX4);
	tex_grave_paralax[4] = Load(GAMEAPI_TEX_GRAVE_PARALAX5);

	tex_candy_paralax[0] = Load(GAMEAPI_TEX_CANDY_PARALAX1);
	tex_candy_paralax[1] = Load(GAMEAPI_TEX_CANDY_PARALAX2);
	tex_candy_paralax[2] = Load(GAMEAPI_TEX_CANDY_PARALAX3);
	tex_candy_paralax[3] = Load(GAMEAPI_TEX_CANDY_PARALAX4);
	tex_candy_paralax[4] = Load(GAMEAPI_TEX_CANDY_PARALAX5);


	tex_forest_level_marker_ = Load(GAMEAPI_TEX_FIREST_LEVEL_MARKER);
	tex_winter_level_marker_ = Load(GAMEAPI_TEX_WINTER_LEVEL_MARKER);
	tex_desert_level_marker_ = Load(GAMEAPI_TEX_DESERT_LEVEL_MARKER);
	tex_grave_level_marker_ = Load(GAMEAPI_TEX_GRAVE_LEVEL_MARKER);
	tex_candy_level_marker_ = Load(GAMEAPI_TEX_CANDY_LEVEL_MARKER);

	vTextureList.push_back(tex_forest_level_marker_);
	vTextureList.push_back(tex_winter_level_marker_);
	vTextureList.push_back(tex_desert_level_marker_);
	vTextureList.push_back(tex_grave_level_marker_);
	vTextureList.push_back(tex_candy_level_marker_);



	tex_stars_0_ = Load(GAMEAPI_TEX_STAR0);  // sve sive
	tex_stars_1_ = Load(GAMEAPI_TEX_STAR1);
	tex_stars_2_ = Load(GAMEAPI_TEX_STAR2);
	tex_stars_3_ = Load(GAMEAPI_TEX_STAR3);

	vTextureList.push_back(tex_stars_0_);
	vTextureList.push_back(tex_stars_1_);
	vTextureList.push_back(tex_stars_2_);
	vTextureList.push_back(tex_stars_3_);



	tex_forest_raw_ = Load(GAMEAPI_TEX_FOREST_RAW);
	tex_winter_raw_ = Load(GAMEAPI_TEX_WINTER_RAW);
	tex_desert_raw_ = Load(GAMEAPI_TEX_DESERT_RAW);
	tex_grave_raw_ = Load(GAMEAPI_TEX_GRAVE_RAW);
	tex_candy_raw_ = Load(GAMEAPI_TEX_CANDY_RAW);

	vTextureList.push_back(tex_forest_raw_);
	vTextureList.push_back(tex_winter_raw_);
	vTextureList.push_back(tex_desert_raw_);
	vTextureList.push_back(tex_grave_raw_);
	vTextureList.push_back(tex_candy_raw_);


	tex_ui_panel_green_up = Load(GAMEAPI_TEX_UI_PANEL_GREEN_UP);
	tex_ui_panel_yellow_up = Load(GAMEAPI_TEX_UI_YELLOW_UP);
	tex_ui_panel_red_up = Load(GAMEAPI_TEX_UI_RED_UP);
	tex_ui_panel_blue_up = Load(GAMEAPI_TEX_UI_BLUE_UP);

	vTextureList.push_back(tex_ui_panel_green_up);
	vTextureList.push_back(tex_ui_panel_yellow_up);
	vTextureList.push_back(tex_ui_panel_red_up);
	vTextureList.push_back(tex_ui_panel_blue_up);

	tex_ui_panel_green_down = Load(GAMEAPI_TEX_UI_GREEN_DOWN);
	tex_ui_panel_yellow_down = Load(GAMEAPI_TEX_UI_YELLOW_DOWN);
	tex_ui_panel_red_down = Load(GAMEAPI_TEX_UI_RED_DOWN);
	tex_ui_panel_blue_down = Load(GAMEAPI_TEX_UI_BLUE_DOWN);
    tex_ui_panel_msg_blue = Load(GAMEAPI_TEX_UI_PANEL_MSG_BLUE);

	tex_ui_panel_pause_up = Load(GAMEAPI_TEX_UI_PAUSE_UP);
	tex_ui_panel_back_ = Load(GAMEAPI_TEX_UI_BACK);

	tex_ui_panel_gray_window_ = Load(GAMEAPI_TEX_UI_PANEL_GRAY);
	tex_ui_textbar_panel_ = Load(GAMEAPI_TEX_UI_TEXTBAR_PANEL_GRAY);

	vTextureList.push_back(tex_ui_panel_green_down);
	vTextureList.push_back(tex_ui_panel_yellow_down);
	vTextureList.push_back(tex_ui_panel_red_down);
	vTextureList.push_back(tex_ui_panel_blue_down);
	vTextureList.push_back(tex_ui_panel_msg_blue);

	vTextureList.push_back(tex_ui_panel_pause_up);
	vTextureList.push_back(tex_ui_panel_back_);

	vTextureList.push_back(tex_ui_panel_gray_window_);
	vTextureList.push_back(tex_ui_textbar_panel_);



	tex_ui_panel_forest_frame_collection_ = Load(GAMEAPI_TEX_UI_PANEL_FOREST_FRAME_COLLECTION);
	tex_ui_panel_winter_frame_collection_ = Load(GAMEAPI_TEX_UI_PANEL_WINTER_FRAME_COLLECTION);

	tex_ui_panel_desert_frame_collection_ = Load(GAMEAPI_TEX_UI_PANEL_DESERT_FRAME_COLLECTION);
	tex_ui_panel_grave_frame_collection_ = Load(GAMEAPI_TEX_UI_PANEL_GRAVE_FRAME_COLLECTION);
	tex_ui_panel_candy_frame_collection_ = Load(GAMEAPI_TEX_UI_PANEL_CANDY_FRAME_COLLECTION);

	vTextureList.push_back(tex_ui_panel_forest_frame_collection_);
	vTextureList.push_back(tex_ui_panel_winter_frame_collection_);
	vTextureList.push_back(tex_ui_panel_desert_frame_collection_);
	vTextureList.push_back(tex_ui_panel_grave_frame_collection_);
	vTextureList.push_back(tex_ui_panel_candy_frame_collection_);


	tex_ui_arrow_left = Load(GAMEAPI_TEX_UI_ARROW_LEFT);
    tex_ui_arrow_right = Load(GAMEAPI_TEX_UI_ARROW_RIGHT);

	vTextureList.push_back(tex_ui_arrow_left);
	vTextureList.push_back(tex_ui_arrow_right);


	texture_world_collections[0] = tex_ui_panel_forest_frame_collection_;
	texture_world_collections[1] = tex_ui_panel_winter_frame_collection_;
	texture_world_collections[2] = tex_ui_panel_desert_frame_collection_;
	texture_world_collections[3] = tex_ui_panel_grave_frame_collection_;
	texture_world_collections[4] = tex_ui_panel_candy_frame_collection_;

	tex_ui_stat_frame = Load(GAMEAPI_TEX_STAT_FRAME);
	vTextureList.push_back(tex_ui_stat_frame);


    tex_ui_gold_frame = Load(GAMEAPI_TEX_GOLD_FRAME);
	tex_ui_animal_frame = Load(GAMEAPI_TEX_ANIMAL_FRAME);
	tex_ui_animal_frameq = Load(GAMEAPI_TEX_ANIMAL_FRAMEQ);

	vTextureList.push_back(tex_ui_gold_frame);
	vTextureList.push_back(tex_ui_animal_frame);
	vTextureList.push_back(tex_ui_animal_frameq);


	tex_balloon_miss = Load(GAMEAPI_BALLOON_MISSED);
	tex_letter_miss = Load(GAMEAPI_LETTER_MISSED);

	vTextureList.push_back(tex_balloon_miss);
	vTextureList.push_back(tex_letter_miss);


	tex_gears_ = Load(GAMEAPI_TEX_GEARS);
	tex_door_exit_ = Load(GAMEAPI_TEX_DOOR_EXIT);
   tex_back_to_game = Load(GAMEAPI_TEX_BACK_TO_GAME);
	tex_arrow_continue = Load(GAMEAPI_TEX_ARROW_CONTINUE);
	tex_music_on = Load(GAMEAPI_MUSIC_ON_PATH);
	tex_music_off = Load(GAMEAPI_MUSIC_OFF_PATH);
	tex_sfx_on = Load(GAMEAPI_SFX_ON_PATH);
	tex_sfx_off = Load(GAMEAPI_SFX_OFF_PATH);

	vTextureList.push_back(tex_gears_);
	vTextureList.push_back(tex_door_exit_);
	vTextureList.push_back(tex_back_to_game);
	vTextureList.push_back(tex_arrow_continue);
	vTextureList.push_back(tex_music_on);
	vTextureList.push_back(tex_music_off);
	vTextureList.push_back(tex_sfx_on);
	vTextureList.push_back(tex_sfx_off);



	LoadAnimals();


#ifdef __ANDROID__
	sound_pop = LoadSound(GAMEAPI_SOUND_POP);

	sound_letter_correct_hit = LoadSound(GAMEAPI_SOUND_CORRECT);
	sound_letter_miss = LoadSound(GAMEAPI_SOUND_MISS);
	sound_forest_bck = LoadSound(GAMEAPI_SOUND_FOREST_BK);
	sound_winter_bck = LoadSound(GAMEAPI_SOUND_WINTER_BK);
	sound_grave_bck = LoadSound(GAMEAPI_SOUND_GRAVE_BK);

	sound_forest_music = LoadMusic(GAMEAPI_SOUND_FOREST_MUSIC);
	sound_winter_music = LoadMusic(GAMEAPI_SOUND_WINTER_MUSIC);
	sound_grave_music = LoadMusic(GAMEAPI_SOUND_GRAVE_MUSIC);
	sound_desert_music = LoadMusic(GAMEAPI_SOUND_DESERT_MUSIC);
	sound_candy_music = LoadMusic(GAMEAPI_SOUND_CANDY_MUSIC);

    sound_main_menu = LoadMusic(GAMEAPI_SOUND_MAIN_MUSIC);
    sound_winner_music = LoadMusic(GAMEAPI_SOUND_MAIN_MUSIC);


	printf("");
#else
	sound_pop = Mix_LoadWAV("data/sound/pop.ogg");

	sound_letter_correct_hit = Mix_LoadWAV("data/sound/letter_correct.ogg");
	sound_letter_miss = Mix_LoadWAV("data/sound/miss.ogg");
	sound_forest_bck  = Mix_LoadWAV("data/sound/forest_background.ogg");
	sound_winter_bck = Mix_LoadWAV("data/sound/winter_background.ogg");
	sound_grave_bck = Mix_LoadWAV("data/sound/graveyard_background.ogg");


    sound_forest_music = Mix_LoadMUS("data/sound/forest_music.ogg");
	sound_winter_music = Mix_LoadMUS("data/sound/winter_music.ogg");
	sound_grave_music = Mix_LoadMUS("data/sound/grave_music.ogg");
	sound_desert_music = Mix_LoadMUS("data/sound/desert_music.ogg");
	sound_candy_music = Mix_LoadMUS("data/sound/candy_music.ogg");

	sound_main_menu = Mix_LoadMUS("data/sound/main_menu.ogg");
    sound_winner_music = Mix_LoadMUS("data/sound/winner.ogg");



	
#endif


	return GAMEAPI_OK;
}


Mix_Chunk* I_cAssetManager::LoadSound(string path)
{
    SDL_RWops* rw = SDL_RWFromFile(path.c_str(), "rb");
    Mix_Chunk* tmp = Mix_LoadWAV_RW(rw, 1);

    if (tmp)
        gLog->AppendLog("Load sound %s = OK", path.c_str());

	string s = Mix_GetError();
	return tmp;
}


Mix_Music *I_cAssetManager::LoadMusic(string path)
{
	SDL_RWops *rw = SDL_RWFromFile(path.c_str(), "rb");
	Mix_Music *tmp = Mix_LoadMUS_RW(rw, 1);

	gLog->AppendLog("ASSET: Load MUSIC %s",path.c_str());
    if (tmp == NULL)
       {
      
	    gLog->AppendLog("Unable to load music: %s",  Mix_GetError());
       }

	string s = Mix_GetError();

	return tmp;
}



void I_cAssetManager::LoadIntroAssets(void)
{
	tex_splash = Load(GAMEAPI_TEX_SPLASH);

}


SDL_Texture *I_cAssetManager::GetStatFrame(void)
{
 return tex_ui_stat_frame;
}


SDL_Texture *I_cAssetManager::GetGoldFrame(void)
{
 return tex_ui_gold_frame;
}


SDL_Texture *I_cAssetManager::GetForestPanel(void)
{
 return tex_ui_forest;
}




SDL_Texture *I_cAssetManager::GetAnimalFrame(void)
{
 return tex_ui_animal_frame;
}
SDL_Texture *I_cAssetManager::GetAnimalFrameq(void)
{
 return tex_ui_animal_frameq;
}


SDL_Texture *I_cAssetManager::GetTODO(void)
{
 return tex_todo;
}




SDL_Texture *I_cAssetManager::GetArrowLeft(void)
{
 return tex_ui_arrow_left;
}


SDL_Texture *I_cAssetManager::GetArrowRight(void)
{
 return tex_ui_arrow_right;
}

SDL_Texture *I_cAssetManager::GetGears(void)
{
 return tex_gears_;
}


SDL_Texture *I_cAssetManager::GetExit(void)
{
 return tex_door_exit_;
}

// lopoci, rupe etc
SDL_Texture *I_cAssetManager::GetLevelSelectButtonTexture(GAMEAPI_WORLD_TYPE type)
{
	switch (type)
	{
	case WORLD_FOREST:
	    return tex_btn_forest_level_;
		break;
	case WORLD_WINTER:
	    return tex_btn_winter_level_;
		break;
	case WORLD_DESERT:
		return tex_btn_desert_level_;
		break;
	case WORLD_GRAVEYARD:
		return tex_btn_grave_level_;
		break;
	case WORLD_CANDYLAND:
		return tex_btn_candy_level_;
		break;
	}

 return NULL;

}

// marker
SDL_Texture *I_cAssetManager::GetLevelMarkerTexture(GAMEAPI_WORLD_TYPE type)
{
	switch (type)
	{
	case WORLD_FOREST:
		return tex_forest_level_marker_;
		break;
	case WORLD_WINTER:
		return tex_winter_level_marker_;
		break;
	case WORLD_DESERT:
		return tex_desert_level_marker_;
		break;
	case WORLD_GRAVEYARD:
		return tex_grave_level_marker_;
		break;
	case WORLD_CANDYLAND:
		return tex_candy_level_marker_;
		break;
	}

}



GAMEAPI_ERROR I_cAssetManager::LoadFont(void)
{

#ifdef __ANDROID__

	SDL_RWops *file = SDL_RWFromFile("font.ttf", "rb");
	game_font_ = TTF_OpenFontRW(file, 1, 64);
	if (game_font_ == NULL)
	{
		printf("ENGINE:InitSDL: Error loading font: %s", TTF_GetError());
		return GAMEAPI_ERROR_LOAD_FONT;
	}

	file = SDL_RWFromFile("font.ttf", "rb");
	game_font_outline_ = TTF_OpenFontRW(file, 1, 64);
	if (game_font_outline_ == NULL)
	{
		printf("ENGINE:InitSDL: Error loading font: %s", TTF_GetError());
		return GAMEAPI_ERROR_LOAD_FONT;
	}

	TTF_SetFontOutline(gAssetManager->game_font_outline_, 2);
	
#else


	game_font_ = TTF_OpenFont(GAMEAPI_FONT_PATH, 64);
	if (!game_font_)
	{
		gLog->AppendLog("I_cAssetManager:LoadFont: Error loading font: %s", TTF_GetError());
		return GAMEAPI_ERROR_LOAD_FONT;
	}

	game_font_outline_ = TTF_OpenFont(GAMEAPI_FONT_PATH, 64);
	if (!game_font_outline_)
	{
		gLog->AppendLog("I_cAssetManager:LoadFont : Error loading font: %s", TTF_GetError());
		return GAMEAPI_ERROR_LOAD_FONT;
	}


#endif

	return GAMEAPI_OK;
}


TTF_Font *I_cAssetManager::GetFont(void)
{
 return game_font_;
}

int I_cAssetManager::LoadPlayerSprite(string file_path)
{




	return  0;
}






//IMG_LoadTexture_RW

SDL_Texture *I_cAssetManager::Load(string path)
{
    SDL_Texture *tmp = NULL;
#ifdef __ANDROID__
	SDL_RWops *file = SDL_RWFromFile(path.c_str(), "rb");
	tmp = IMG_LoadTexture_RW(ptr_renderer_,file,NULL);
#else 
	tmp = IMG_LoadTexture(ptr_renderer_, path.c_str());
#endif

	if (tmp)
   return tmp;

 return NULL;
}



// Blue
void I_cAssetManager::LoadBlue(void)
{

	char path[256];

	for (int c=0;c< GAMEAPI_BALLOON_SPRITE_COUNT;c++)
	    {
		   sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_BLUE, c + 1);
			 SDL_Texture *tex = Load(path);
			 vTexBalloonBlue.push_back(tex);
			}

}

// orange
void I_cAssetManager::LoadOrange(void)
{
	char path[256];

	for (int c = 0; c < GAMEAPI_BALLOON_SPRITE_COUNT; c++)
	{
		sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_ORANGE, c + 1);
		SDL_Texture *tex = Load(path);
		vTexBalloonOrange.push_back(tex);
	}

}


// Green
void I_cAssetManager::LoadGreen(void)
{
	char path[256];

	for (int c = 0; c < GAMEAPI_BALLOON_SPRITE_COUNT; c++)
	{
		sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_GREEN, c + 1);
		SDL_Texture *tex = Load(path);
		vTexBalloonGreen.push_back(tex);
	}

}

// purple
void I_cAssetManager::LoadPurple(void)
{
	char path[256];


	for (int c = 0; c < GAMEAPI_BALLOON_SPRITE_COUNT; c++)
	{
		sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_PURPLE, c + 1);
		SDL_Texture *tex = Load(path);
		vTexBalloonPurple.push_back(tex);
	}


}


// Pink
void I_cAssetManager::LoadPink(void)
{
	char path[256];


	for (int c = 0; c < GAMEAPI_BALLOON_SPRITE_COUNT; c++)
	{
		sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_PINK, c + 1);
		SDL_Texture *tex = Load(path);
		vTexBalloonPink.push_back(tex);
	}

}

// red
void I_cAssetManager::LoadRed(void)
{
	char path[256];


	for (int c = 0; c < GAMEAPI_BALLOON_SPRITE_COUNT; c++)
	{
		sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_RED, c + 1);
		SDL_Texture *tex = Load(path);
		vTexBalloonRed.push_back(tex);
	}

}

// yellow
void I_cAssetManager::LoadYellow(void)
{
	char path[256];


	for (int c = 0; c < GAMEAPI_BALLOON_SPRITE_COUNT; c++)
	{
		sprintf(path, "%s/1%d.png", GAMEAPI_BALLOON_PATH_YELLOW, c + 1);
		SDL_Texture *tex = Load(path);
		vTexBalloonYellow.push_back(tex);
	}
}


TTF_Font *I_cAssetManager::GetFontOutline(void)
{
 return game_font_outline_;
}


SDL_Renderer *I_cAssetManager::GetRenderer(void)
{
 return ptr_renderer_;
}


Mix_Chunk *I_cAssetManager::GetSound_Pop(void)
{
  return sound_pop;
}

Mix_Chunk *I_cAssetManager::GetSound_LetterHit(void)
{
	return sound_letter_correct_hit;
}

Mix_Chunk *I_cAssetManager::GetSound_LetterMiss(void)
{
	return sound_letter_miss;
}


Mix_Chunk *I_cAssetManager::GetSound_ForestBackground(void)
{
	return sound_forest_bck;
}

Mix_Chunk *I_cAssetManager::GetSound_WinterBackground(void)
{
	return sound_winter_bck;
}

Mix_Chunk *I_cAssetManager::GetSound_GraveBackground(void)
{
	return sound_grave_bck;
}


Mix_Music *I_cAssetManager::GetMusic_MainMenu(void)
{
 return sound_main_menu;
}

Mix_Music *I_cAssetManager::GetMusic_Forest(void)
{
 return sound_forest_music;
}


Mix_Music *I_cAssetManager::GetMusic_Winter(void)
{
 return sound_winter_music;
}


Mix_Music *I_cAssetManager::GetMusic_Graveyard(void)
{
 return sound_grave_music;
}



Mix_Music *I_cAssetManager::GetMusic_Desert(void)
{
 return sound_desert_music;
}


Mix_Music *I_cAssetManager::GetMusic_Candy(void)
{
 return sound_candy_music;
}

Mix_Music *I_cAssetManager::GetMusic_Winner(void)
{
 return sound_winner_music;
}




SDL_Texture *I_cAssetManager::GetWorldBackground(GAMEAPI_WORLD_TYPE type)
{
 return texture_world_background[type];
}


SDL_Texture *I_cAssetManager::GetCollectionsWindow(GAMEAPI_WORLD_TYPE type)
{
	return texture_world_collections[type];
}


SDL_Texture *I_cAssetManager::GetLevelBackground(GAMEAPI_WORLD_TYPE type)
{
 return texture_level_background[type];
}


SDL_Texture *I_cAssetManager::GetWorldSelectButton(GAMEAPI_WORLD_TYPE type)
{
 switch (type)
			  {
				 case WORLD_FOREST:
				  return tex_btn_forest_select_;
				 case WORLD_WINTER:
				  return tex_btn_winter_select_;
				 case WORLD_DESERT:
					return tex_btn_desert_select_;
				 case WORLD_GRAVEYARD:
					return tex_btn_grave_select_;
				 case WORLD_CANDYLAND:
				  return tex_btn_candy_select_;
				 default:
				  return NULL;
				}

 return NULL;
}




SDL_Texture *I_cAssetManager::GetUIButton(GAMEAPI_BUTTON_COLOR color, bool button_up)
{

	switch (color)
        {
				 case BUTTON_COLOR_GREEN:
				  if (button_up) return tex_ui_panel_green_up; else return tex_ui_panel_green_down;
				 case BUTTON_COLOR_YELLOW:
					 if (button_up) return tex_ui_panel_yellow_up; else return tex_ui_panel_yellow_down;
				 case BUTTON_COLOR_BLUE:
					 if (button_up) return tex_ui_panel_blue_up; else return tex_ui_panel_blue_down;
				 case BUTTON_COLOR_RED:
					 if (button_up) return tex_ui_panel_red_up; else return tex_ui_panel_red_down;
		     default:
				  return NULL;
	      }

 return NULL;
}


SDL_Texture *I_cAssetManager::GetPanelMsgBlue(void)
{
	return tex_ui_panel_msg_blue;
}


SDL_Texture *I_cAssetManager::GetTextbarPanel(void)
{
	return tex_ui_textbar_panel_;
}


SDL_Texture *I_cAssetManager::GetBalloonMiss(void)
{
	return tex_balloon_miss;
}

SDL_Texture *I_cAssetManager::GetLetterMiss(void)
{
	return tex_letter_miss;
}

SDL_Texture * I_cAssetManager::GetBackToGame(void)
{
 return tex_back_to_game;
}

SDL_Texture * I_cAssetManager::GetSplash()
{
	 return tex_splash;
}

SDL_Texture * I_cAssetManager::GetLoading()
{
	return tex_loading;
}

SDL_Texture * I_cAssetManager::GetArrowContinue(void)
{
	return tex_arrow_continue;
}




SDL_Texture *I_cAssetManager::GetBalloon_Unknown()
{
 return tex_balloon_unknow;
}


SDL_Texture *I_cAssetManager::GetBalloon(GAMEAPI_BALLOON_COLOR color)
{

	switch (color)
	{
	 

	case GAMEAPI_BALLOON_COLOR_BLUE:
		return vTexBalloonBlue[0];
		break;

	case GAMEAPI_BALLOON_COLOR_GREEN:
		return vTexBalloonGreen[0];
		break;

	case GAMEAPI_BALLOON_COLOR_ORANGE:
		return vTexBalloonOrange[0];
		break;

	case GAMEAPI_BALLOON_COLOR_PINK:
		return vTexBalloonPink[0];
		break;

	case GAMEAPI_BALLOON_COLOR_PURPLE:
		return vTexBalloonPurple[0];
		break;

	case GAMEAPI_BALLOON_COLOR_RED:
		return vTexBalloonRed[0];
		break;

	case GAMEAPI_BALLOON_COLOR_YELLOW:
		return vTexBalloonYellow[0];
		break;

	default: break;
	}
	
	return NULL;
}



SDL_Texture **I_cAssetManager::GetParalaxLayer(GAMEAPI_WORLD_TYPE type, int num)
{
	switch (type)
	{
	case WORLD_FOREST:
		return &tex_forest_paralax[num];
	case WORLD_WINTER:
		return &tex_winter_paralax[num];
	case WORLD_DESERT:
		return &tex_desert_paralax[num];
	case WORLD_GRAVEYARD:
		return &tex_grave_paralax[num];
	case WORLD_CANDYLAND:
		return &tex_candy_paralax[num];
	default:
		return NULL;
	}

}


SDL_Texture *I_cAssetManager::GetStars(int count)
{
 switch(count)
       {
			  case 0: return tex_stars_0_; // no stars
				case 1: return tex_stars_1_; 
				case 2: return tex_stars_2_;
				case 3: return tex_stars_3_;
			 }

}


SDL_Texture *I_cAssetManager::GetStarGold(void)
{
 return tex_star_gold_;
}

SDL_Texture *I_cAssetManager::GetStarGray(void)
{
 return tex_star_gray_;
}

SDL_Texture * I_cAssetManager::GetBackToMenu(void)
{
	return tex_ui_panel_back_;
}

SDL_Texture * I_cAssetManager::GetPause(void)
{
	return tex_ui_panel_pause_up;
}

/*
SDL_Texture * I_cAssetManager::GetForestFrame(void)
{
	return tex_ui_panel_forest_frame_;
}*/



SDL_Texture * I_cAssetManager::GetForestCollectionFrame(void)
{
	return tex_ui_panel_forest_frame_collection_;
}



/*
SDL_Texture *I_cAssetManager::GetWinterFrame(void)
{
 return tex_ui_panel_winter_frame_;
}*/


SDL_Texture *I_cAssetManager::GetWinterCollectionFrame(void)
{
 return tex_ui_panel_winter_frame_collection_;
}


SDL_Texture *I_cAssetManager::GetDesertFrame(void)
{
 return NULL;
}

SDL_Texture *I_cAssetManager::GetDesertCollectionFrame(void)
{
 
	return NULL;
}

SDL_Texture *I_cAssetManager::GetGraveFrame(void)
{
	return NULL;
}

SDL_Texture *I_cAssetManager::GetGraveCollectionFrame(void)
{
	return NULL;
}

SDL_Texture *I_cAssetManager::GetCandyFrame(void)
{
	return NULL;
}

SDL_Texture *I_cAssetManager::GetCandyCollectionFrame(void)
{
	return NULL;
}


// old tests
void I_cAssetManager::file_read(const char* filename) 
{
/*
	vector<string>vtmpstr;

	SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
	if (rw == NULL) 
	   {
		  // TODO: return error;
		 }

	Sint64 res_size = SDL_RWsize(rw);
	char* res = (char*)malloc(res_size + 1);

	Sint64 nb_read_total = 0, nb_read = 1;
	char* buf = res;
	while (nb_read_total < res_size && nb_read != 0) {
		nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(rw);
	if (nb_read_total != res_size) {
		free(res);
		return NULL;
	}

	res[nb_read_total] = '\0';

	string stmp;
	for (int c=0;c< nb_read_total;c++)
	    {
			 if (res[c] == '\r')
			    {
					 c+=2;
					 vtmpstr.push_back(stmp);
					 stmp.clear();
					}
			 stmp += res[c];
	}

	*/
}




int I_cAssetManager::LoadAnimals(void)
{
 vector<string>vtmpstr;

#ifdef __ANDROID__

 // Load animas file

 SDL_RWops *rw = SDL_RWFromFile("animals.dat", "rb");
 if (rw == NULL) return NULL;

 Sint64 res_size = SDL_RWsize(rw);
 char* res = (char*)malloc(res_size + 1);

 Sint64 nb_read_total = 0, nb_read = 1;
 char* buf = res;
 while (nb_read_total < res_size && nb_read != 0) {
	 nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
	 nb_read_total += nb_read;
	 buf += nb_read;
}
 SDL_RWclose(rw);
 if (nb_read_total != res_size) {
	 free(res);
	 return NULL;
 }

 res[nb_read_total] = '\0';

 string stmp;
 for (int c = 0; c < nb_read_total; c++)
 {
	 if (res[c] == '\r')
	 {
		 c += 2;
		 vtmpstr.push_back(stmp);
		 stmp.clear();
	 }
	 stmp += res[c];
 }


 

#else
 std::ifstream f(GAMEAPI_ANIMALSDATA_PATH, std::ifstream::in);
 if (f.fail())
 {
	 // TODO: not good. No animal spec file
	 return -1;
 }


 	string str;
 	while (std::getline(f, str))
 	{
 #ifdef __ANDROID__
 		str.erase(str.size()-1);   // Android and Linux will include 'CR' to ther read line. So a line will always be read
 #endif
 		vtmpstr.push_back(str);
 	}

	 f.close();


#endif



#ifdef __ANDROID__
	string str_animals_path = GAMEAPI_ANIMALS_PATH;
#else
	string str_animals_path = GAMEAPI_ANIMALS_PATH + string("/");
#endif

	for (int c=0;c< ANIMAL_COUNT;c++)
     {
		  //string str_animal = "animals/owl.png";
		  string str_animal = str_animals_path + vtmpstr[c] + ".png";
			string str_animal_gold = str_animals_path + vtmpstr[c] + "_gold.png";
			SDL_Texture *tex = Load(str_animal);
			SDL_Texture *tex_gold = Load(str_animal_gold);

			if (tex) 
			   {
				  mAnimalList[c] = tex;
				 }else {
				        gLog->AppendLog("Unable to load animal texture: %s", str_animal.c_str());
								mAnimalList[c] = GetTODO();
							 }

				 if (tex_gold)
				 {
					 //mAnimalGoldList[c] = tex_gold;
					 mAnimalGoldList[c] = tex_gold;
				 }else {
				         gLog->AppendLog("Unable to load gold texture: %s", str_animal_gold.c_str());
								 mAnimalGoldList[c] = GetTODO();
								}


			mAnimalStringMap[c] = vtmpstr[c];
		 }



return 0;
}




SDL_Texture *I_cAssetManager::GetAnimal(GAMEAPI_ANIMAL a)
{
 return mAnimalList[a];
 //return NULL;
}

SDL_Texture *I_cAssetManager::GetAnimalGold(GAMEAPI_ANIMAL a)
{
	return mAnimalGoldList[a];
	//return NULL;
}


SDL_Texture *I_cAssetManager::GetAnimal(int world, int level)
{
  int num = (level) += (world * GAMEAPI_LEVEL_COUNT);
	return mAnimalList[num];
}




SDL_Texture *I_cAssetManager::GetMusicOn(void)
{
 return tex_music_on;
}

SDL_Texture *I_cAssetManager::GetMusicOff(void)
{
 return tex_music_off;
}

SDL_Texture *I_cAssetManager::GetSfxOn(void)
{
	return tex_sfx_on;
}

SDL_Texture *I_cAssetManager::GetSfxOff(void)
{
	return tex_sfx_off;
}



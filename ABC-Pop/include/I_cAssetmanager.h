#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "gameapi.h"


class I_cAssetManager
{
public:
	I_cAssetManager();
	~I_cAssetManager();

	void Init(SDL_Renderer *rend);
	GAMEAPI_ERROR LoadAssets(void);
	void LoadIntroAssets(void);


	Mix_Chunk *LoadSound(string path);
	Mix_Music *LoadMusic(string path);

	TTF_Font *GetFont();
	SDL_Texture *Load(string path);

	SDL_Texture *GetLevelSelectButtonTexture(GAMEAPI_WORLD_TYPE type);
	SDL_Texture *GetLevelMarkerTexture(GAMEAPI_WORLD_TYPE type);

	void file_read(const char* filename);

	GAMEAPI_ERROR LoadFont(void);


private:

	int LoadPlayerSprite(string file_path);

	void LoadBlue(void);
	void LoadGreen(void);
	void LoadOrange(void);
	void LoadPurple(void);
	void LoadPink(void);
	void LoadRed(void);
	void LoadYellow(void);



	int LoadAnimals(void);

    vector<SDL_Texture *> vTextureList;

//

public:
	private:

	// color panels
	SDL_Texture *texture_green_panel_;
	SDL_Texture *texture_blue_panel_;
	SDL_Texture *texture_yellow_panel_;
	SDL_Texture *texture_red_panel_;

	SDL_Texture *texture_life_;



	SDL_Texture *texture_level_background[WORLD_COUNT];
	SDL_Texture *texture_world_background[WORLD_COUNT];
	SDL_Texture *texture_world_collections[WORLD_COUNT];



	SDL_Texture *tex_star_gold_;
	SDL_Texture *tex_star_gray_;


	SDL_Texture *tex_hud_blue_rect_;
	SDL_Texture *tex_hud_green_rect_;
	SDL_Texture *tex_hud_orange_rect_;
	SDL_Texture *tex_hud_pink_rect_;
	SDL_Texture *tex_hud_purple_rect_;
	SDL_Texture *tex_hud_red_rect_;
	SDL_Texture *tex_hud_red_wide_rect_;
	SDL_Texture *tex_hud_yellow_rect_;

	SDL_Texture *tex_ui_story_panel_;


  // joker
	SDL_Texture *tex_balloon_unknow;





	SDL_Texture *tex_btn_forest_select_;
	SDL_Texture *tex_btn_winter_select_;
	SDL_Texture *tex_btn_desert_select_;
	SDL_Texture *tex_btn_grave_select_;
	SDL_Texture *tex_btn_candy_select_;

	SDL_Texture *tex_btn_forest_level_;
	SDL_Texture *tex_btn_winter_level_;
	SDL_Texture *tex_btn_desert_level_;
	SDL_Texture *tex_btn_grave_level_;
	SDL_Texture *tex_btn_candy_level_;


	vector<SDL_Texture*>vAnimalList;


	map<int, string>mAnimalNameMap;
	map<int, SDL_Texture *>mAnimalList; 
	map<int, SDL_Texture *>mAnimalGoldList;

	
	SDL_Texture *tex_animal_frog_;
	SDL_Texture *tex_animal_turtle_;
	SDL_Texture *tex_animal_hedge_;
	SDL_Texture *tex_animal_rabbit_;
	SDL_Texture *tex_animal_snail_;
	SDL_Texture *tex_animal_deer_;
	

	SDL_Texture *tex_forest_paralax[5];
	SDL_Texture *tex_winter_paralax[5];
	SDL_Texture *tex_desert_paralax[5];
	SDL_Texture *tex_grave_paralax[5];
	SDL_Texture *tex_candy_paralax[5];

	SDL_Texture *tex_ui_panel_green_up;
	SDL_Texture *tex_ui_panel_yellow_up;
	SDL_Texture *tex_ui_panel_red_up;
	SDL_Texture *tex_ui_panel_blue_up;

	SDL_Texture *tex_ui_panel_green_down;
	SDL_Texture *tex_ui_panel_yellow_down;
	SDL_Texture *tex_ui_panel_red_down;
	SDL_Texture *tex_ui_panel_blue_down;
	SDL_Texture *tex_ui_panel_pause_up;
	SDL_Texture *tex_ui_panel_gray_window_;
    SDL_Texture *tex_ui_panel_msg_blue;
	
	SDL_Texture *tex_ui_textbar_panel_;


	SDL_Texture *tex_ui_panel_forest_frame_collection_;

  SDL_Texture *tex_ui_panel_winter_frame_collection_;

	SDL_Texture *tex_ui_panel_desert_frame_collection_;
	SDL_Texture *tex_ui_panel_grave_frame_collection_;
	SDL_Texture *tex_ui_panel_candy_frame_collection_;


	SDL_Texture *tex_ui_panel_back_;


	SDL_Texture *tex_forest_level_marker_;
	SDL_Texture *tex_winter_level_marker_;
	SDL_Texture *tex_desert_level_marker_;
	SDL_Texture *tex_grave_level_marker_;
	SDL_Texture *tex_candy_level_marker_;

	SDL_Texture *tex_stars_0_;
	SDL_Texture *tex_stars_1_;
	SDL_Texture *tex_stars_2_;
	SDL_Texture *tex_stars_3_;
	

	SDL_Texture *tex_forest_raw_;
	SDL_Texture *tex_winter_raw_;
	SDL_Texture *tex_desert_raw_;
	SDL_Texture *tex_grave_raw_;
	SDL_Texture *tex_candy_raw_;

	SDL_Texture *tex_ui_arrow_left;
	SDL_Texture *tex_ui_arrow_right;

	SDL_Texture *tex_ui_stat_frame;
	SDL_Texture *tex_ui_gold_frame;
	SDL_Texture *tex_ui_forest;

	SDL_Texture *tex_ui_animal_frame;
	SDL_Texture *tex_ui_animal_frameq;

	SDL_Texture *tex_balloon_miss;
	SDL_Texture *tex_letter_miss;

	SDL_Texture *tex_gears_;
	SDL_Texture *tex_door_exit_;

	SDL_Texture *tex_todo;

	SDL_Texture *tex_back_to_game;

	SDL_Texture *tex_splash;
	SDL_Texture *tex_loading;

	SDL_Texture *tex_arrow_continue;

	SDL_Texture *tex_music_on;
	SDL_Texture *tex_music_off;

	SDL_Texture *tex_sfx_on;
	SDL_Texture *tex_sfx_off;



	Mix_Chunk *sound_pop;
	Mix_Chunk *sound_letter_correct_hit;
	Mix_Chunk *sound_letter_miss;

	Mix_Chunk *sound_forest_bck;
	Mix_Chunk *sound_winter_bck;
	Mix_Chunk *sound_grave_bck;

	Mix_Music *sound_main_menu;
	Mix_Music *sound_forest_music;
	Mix_Music *sound_winter_music;
	Mix_Music *sound_grave_music;
	Mix_Music *sound_desert_music;
	Mix_Music *sound_candy_music;
	Mix_Music *sound_winner_music;



	SDL_Renderer *ptr_renderer_;


	TTF_Font *game_font_outline_;
	TTF_Font *game_font_;



private:

	public:
		   Mix_Chunk *GetSound_Pop(void);
			 Mix_Chunk *GetSound_LetterHit(void);
			 Mix_Chunk *GetSound_LetterMiss(void);
			 Mix_Chunk *GetSound_ForestBackground(void);
			 Mix_Chunk *GetSound_WinterBackground(void);
			 Mix_Chunk *GetSound_GraveBackground(void);
			 Mix_Music *GetMusic_MainMenu(void);
			 Mix_Music *GetMusic_Forest(void);
			 Mix_Music *GetMusic_Winter(void);
			 Mix_Music *GetMusic_Graveyard(void);
			 Mix_Music *GetMusic_Desert(void);
			 Mix_Music *GetMusic_Candy(void);
             Mix_Music *GetMusic_Winner(void);


				TTF_Font *GetFontOutline(void);
				SDL_Renderer *GetRenderer(void);
				SDL_Texture *GetWorldBackground(GAMEAPI_WORLD_TYPE type);
				SDL_Texture *GetLevelBackground(GAMEAPI_WORLD_TYPE type);
				SDL_Texture *GetCollectionsWindow(GAMEAPI_WORLD_TYPE type);

				SDL_Texture *GetWorldSelectButton(GAMEAPI_WORLD_TYPE type);
				SDL_Texture *GetUIButton(GAMEAPI_BUTTON_COLOR color, bool button_up);
				SDL_Texture *GetAnimal(GAMEAPI_ANIMAL animal);
				SDL_Texture *GetAnimal(int world, int level);
				SDL_Texture *GetAnimalGold(GAMEAPI_ANIMAL a);

				SDL_Texture *GetBalloon_Unknown();
				SDL_Texture *GetBalloon(GAMEAPI_BALLOON_COLOR color);
				SDL_Texture **GetParalaxLayer(GAMEAPI_WORLD_TYPE type, int num);
				SDL_Texture *GetStars(int count);
				SDL_Texture *GetStarGold(void);
				SDL_Texture *GetStarGray(void);
				SDL_Texture *GetBackToMenu(void);
				SDL_Texture *GetPause(void);

				SDL_Texture *GetArrowLeft(void);
				SDL_Texture *GetArrowRight(void);

				SDL_Texture *GetGears(void);
				SDL_Texture *GetExit(void);

				//SDL_Texture *GetForestFrame(void);
				SDL_Texture *GetForestCollectionFrame(void);

				//SDL_Texture *GetWinterFrame(void);
				SDL_Texture *GetWinterCollectionFrame(void);

				SDL_Texture *GetDesertFrame(void);
				SDL_Texture *GetDesertCollectionFrame(void);

				SDL_Texture *GetGraveFrame(void);
				SDL_Texture *GetGraveCollectionFrame(void);

				SDL_Texture *GetCandyFrame(void);
				SDL_Texture *GetCandyCollectionFrame(void);

				SDL_Texture *GetStatFrame(void);
				SDL_Texture *GetGoldFrame(void);
				SDL_Texture *GetForestPanel(void);

				SDL_Texture *GetAnimalFrame(void);
				SDL_Texture *GetAnimalFrameq(void);
				
				SDL_Texture *GetTODO(void);

				SDL_Texture *GetTextbarPanel(void);
                SDL_Texture *GetPanelMsgBlue(void);

				SDL_Texture *GetBalloonMiss(void);
				SDL_Texture *GetLetterMiss(void);

				SDL_Texture *GetBackToGame(void);

				SDL_Texture *GetSplash();
				SDL_Texture *GetLoading();

				SDL_Texture *GetArrowContinue(void);

				SDL_Texture *GetMusicOn(void);
				SDL_Texture *GetMusicOff(void);

				SDL_Texture *GetSfxOn(void);
				SDL_Texture *GetSfxOff(void);

				vector<SDL_Texture*> vTexBalloonBlue;;

				vector<SDL_Texture*> vTexBalloonOrange;
				vector<SDL_Texture*> vTexBalloonGreen;
				vector<SDL_Texture*> vTexBalloonPink;
				vector<SDL_Texture*> vTexBalloonPurple;
				vector<SDL_Texture*> vTexBalloonRed;
				vector<SDL_Texture*> vTexBalloonYellow;



				vector<SDL_Texture*> *vptrTexBalloonBlue;
				vector<SDL_Texture*> *vptrTexBalloonGreen;
				vector<SDL_Texture*> *vptrTexBalloonOrange;
				vector<SDL_Texture*> *vptrTexBalloonPink;
				vector<SDL_Texture*> *vptrTexBalloonPurple;
				vector<SDL_Texture*> *vptrTexBalloonRed;
				vector<SDL_Texture*> *vptrTexBalloonYellow;




};



extern I_cAssetManager *gAssetManager;
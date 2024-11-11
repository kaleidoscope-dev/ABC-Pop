#pragma once




#define GAMEAPI_RELEASE 1

#define GAMEAPI_GAME_VERSION "v-A.1.0.0-Release"

#define GAMEAPI_FPS_STEP 16.6
#define GAMEAPI_FPS 60


#define GAMEAPI_PI 3.14159



#define GAMEAPI_PLAYER_W 110
#define GAMEAPI_PLAYER_H 80


#define GAMEAPI_SURFACE_W 5
#define GAMEAPI_SURFACE_H 5

#define GAMEAPI_DIAMOND_W 20
#define GAMEAPI_DIAMOND_H 20

#define GAMEAPI_TILE_W 10
#define GAMEAPI_TILE_H 10

#define GAMEAPI_CRITTER_START_HEIGHT 450

#define GAMEAPI_COLLISION_BIT_NULL 0x0000           // 0 
#define GAMEAPI_COLLISION_BIT_SURFACE 0x0001    // 1
#define GAMEAPI_COLLISION_BIT_CRITTER 0x0002   // 2
#define GAMEAPI_COLLISION_BIT_SENSOR  0x0004   // 4
#define GAMEAPI_COLLISION_BIT_DIAMOND 0x0008   // 8
#define GAMEAPI_COLLISION_BIT_BLOOD 0x0010     //16
#define GAMEAPI_COLLISION_BIT_PLAYER 0x0020    // 32
//#define GAMEAPI_COLLISION_BIT_ 0x0040
//#define GAMEAPI_COLLISION_BIT_ 0x0080
//
#define GAMEAPI_BALLOON_SPRITE_COUNT 6

#define GAMEAPI_LEVEL_COUNT 6

#define GAMEAPI_PHASE_1 1   // before finishing the game 
#define GAMEAPI_PHASE_2 2   // aftter


typedef struct GAMEAPI_TEXT_PAIR
{
	uint16_t index;
	const char *name;
}GAMEAPI_TEXT_PAIR;



typedef enum GAMEAPI_Letter
{
	LETTER_A,
	LETTER_B,
	LETTER_C,
	LETTER_D,
	LETTER_E,
	LETTER_F,
	LETTER_G,
	LETTER_H,
	LETTER_I,
	LETTER_J,
	LETTER_K,
	LETTER_L,
	LETTER_M,
	LETTER_N,
	LETTER_O,
	LETTER_P,
	LETTER_R,
	LETTER_S,
	LETTER_T,
	LETTER_U,
	LETTER_V,
	LETTER_W,
	LETTER_X,
	LETTER_Y,
	LETTER_Z,
	LETTER_COUNT
}GAMEAPI_LETTER_TYPE;




typedef enum GAMEAPI_Event_Type
{

	GAMEAPI_EVENT_NO_EVENT,
	GAMEAPI_EVENT_QUIT,
	GAMEAPI_EVENT_KEY_LEFT,
	GAMEAPI_EVENT_KEY_RIGHT,
	GAMEAPI_EVENT_KEY_UP,
	GAMEAPI_EVENT_KEY_DOWN,
	GAMEAPI_EVENT_KEY_ESC,
	GAMEAPI_EVENT_LMOUSE_DOWN,
	GAMEAPI_EVENT_LMOUSE_UP,
	GAMEAPI_EVENT_LMOUSE_CLICK,
	GAMEAPI_EVENT_RMOUSE_CLICK,
	GAMEAPI_EVENT_KEY_TEST_KEY, // t
	GAMEAPI_EVENT_KEY_START,
	GAMEAPI_EVENT_GAME_OVER,  

	// balloons
	GAMEAPI_EVENT_CREATE_BALLOON,
	GAMEAPI_EVENT_CREATE_WINNER_BALLOON,


	// critters
	GAMEAPI_EVENT_CREATE_CRITTER,
	GAMEAPI_EVENT_POP_BALLOON,   
	GAMEAPI_EVENT_DELETE_CRITTER,    

	// win/lose 
	GAMEAPI_EVENT_LOSER,
	GAMEAPI_EVENT_WINNER,

	// updates
	GAMEAPI_EVENT_UPDATE_SCORE,
	GAMEAPI_EVENT_UPDATE_MISS,
	GAMEAPI_EVENT_UPDATE_HIT,
	GAMEAPI_EVENT_UPDATE_TIME,
	GAMEAPI_EVENT_UPDATE_STARS,

	GAMEAPI_EVENT_CREATE_WEAPON,
	GAMEAPI_EVENT_CREATE_DIAMOND,
	GAMEAPI_EVENT_CREATE_BLOOD_DROPLET,

	GAMEAPI_EVENT_CREATE_LETTER,
	GAMEAPI_EVENT_CREATE_JOKER,

	GAMEAPI_EVENT_POP_ANIMAL,

	GAMEAPI_EVENT_TYPE_CHANGE_WEAPON,

	GAMEAPI_EVENT_LEVEL_COMPLETE,
	GAMEAPI_EVENT_WORLD_COMPLETE,

	GAMEAPI_EVENT_GAME_FINISHED,

	GAMEAPI_EVENT_SET_UI_STATE,
	GAMEAPI_EVENT_ON_NEXT_LEVEL,     // call from LeveCompleteWindow continue.onClick
	GAMEAPI_EVENT_WORLD_COMPLETE_CONTINUE,
	GAMEAPI_EVENT_WORLD_SELECT,

	GAMEAPI_EVENT_PAUSE_GAME,
	GAMEAPI_EVENT_RESUME_GAME,
	GAMEAPI_EVENT_QUIT_CURRENT_GAME,

	GAMEAPI_EVENT_PHASE_FINISHED,

	// Main window
	GAMEAPI_EVENT_QUIT_GAME,
	GAMEAPI_EVENT_SHOW_COLLECTION,
	GAMEAPI_EVENT_START_GAME,
	GAMEAPI_EVENT_SHOW_OPTIONS,
	GAMEAPI_EVENT_RESET_GAME,
	GAMEAPI_EVENT_SHOW_CREDITS,

	GAMEAPI_EVENT_MAX_EVENTS
}GAMEAPI_EVENT_TYPE;



typedef enum GAMEAPI_Balloon_Color
{
	GAMEAPI_BALLOON_COLOR_NULL,
	GAMEAPI_BALLOON_COLOR_BLUE,
	GAMEAPI_BALLOON_COLOR_GREEN,
	GAMEAPI_BALLOON_COLOR_RED,
	GAMEAPI_BALLOON_COLOR_YELLOW,
	GAMEAPI_BALLOON_COLOR_ORANGE,
	GAMEAPI_BALLOON_COLOR_PINK,
	GAMEAPI_BALLOON_COLOR_PURPLE,
	GAMEAPI_BALLOON_COLOR_COUNT,
}GAMEAPI_BALLOON_COLOR;



typedef enum GAMEAPI_Balloon_Type
{
	GAMEAPI_BALLOON_TYPE_DEFAULT = 0,
	GAMEAPI_BALLOON_TYPE_SHINY,
	GAMEAPI_BALLOON_TYPE_2,
	GAMEAPI_BALLOON_TYPE_3,
	GAMEAPI_BALLOON_TYPE_4,
	GAMEAPI_BALLOON_TYPE_5,
	GAMEAPI_BALLOON_TYPE_6,
	GAMEAPI_BALLOON_TYPE_COUNT
}GAMEAPI_BALLOON_TYPE;





typedef enum GAMEAPI_UI_Panel_Type
{
	GAMEAPI_UI_PANEL_NULL,
	GAMEAPI_UI_PANEL_START,
	GAMEAPI_UI_PANEL_ARCADE,
	GAMEAPI_UI_PANEL_QUIT,
	GAMEAPI_UI_PANEL_MENU_BACK,
	GAMEAPI_UI_PANEL_RESUME,
	GAMEAPI_UI_PANEL_QUIT_CURRENT,
	GAMEAPI_UI_PANEL_TEXT,
	GAMEAPI_UI_PANEL_CREDITS,
}GAMEAPI_UI_PANEL_TYPE;



// mora ibit ovdje
typedef enum GAMEAPI_GameState
{
	GAMESTATE_RUNNING = 0,
	//GAMESTATE_PAUSED,
	GAMESTATE_UI,
	GAMESTATE_SHOP,
	GAMESTATE_WALK_OF_SHAME,
	GAMESTATE_TAP_TO_CONTINUE,
	//GAMESTATE_WINNER,

}GAMEAPI_GAMESTATE;


typedef enum GAMEAPI_UIState
{
	GAMEAPI_UI_MAIN_MENU,
	GAMEAPI_UI_PAUSED,
	GAMEAPI_UI_CREDITS,
	GAMEAPI_UI_WORLD_SELECT,
	GAMEAPI_UI_FOREST_LEVEL_SELECT,
	GAMEAPI_UI_WINTER_LEVEL_SELECT,
	GAMEAPI_UI_DESERT_LEVEL_SELECT,
	GAMEAPI_UI_GRAVEYARD_LEVEL_SELECT,
	GAMEAPI_UI_CANDYLAND_LEVEL_SELECT,
	GAMEAPI_UI_IDLE,  // igra radi, pokazi samo back button
	GAMEAPI_UI_LEVEL_COMPLETE,
	GAMEAPI_UI_WORLD_COMPLETE,
	GAMEAPI_UI_COLLECTIONS_SELECT,
	GAMEAPI_UI_ANIMAL_COLLECTION_SELECT,
	GAMEAPI_UI_DICTIONARY_SELECT,
	GAMEAPI_UI_KEYBOARD_SELECT,
	GAMEAPI_UI_GAME_OVER,
	GAMEAPI_UI_PHASE_OVER,
	GAMEAPI_UI_SETTINGS_SELECT,
   GAMEAPI_UI_RESET_SELECT
}GAMEAPI_UI_STATE;

typedef enum GAMEAPI_Error
{
	GAMEAPI_OK = 0,
	GAMEAPI_ERROR_SDL_INIT,
	GAMEAPI_ERROR_CREATE_WINDOW,
	GAMEAPI_ERROR_CREATE_RENDER,
	GAMEAPI_ERROR_IMG_INIT,
	GAMEAPI_ERROR_TTF_INIT,
	GAMEAPI_ERROR_MIX_INIT,
	GAMEAPI_ERROR_LOAD_FONT,
	GAMEAPI_ERROR_MAP_PARSING_ERROR,
	GAMEAPI_ERROR_INVALID_FILENAME,
	GAMEAPI_ERROR_LOAD_GAME_DATA,
	GAMEAPI_ERROR_SAVE_GAME_DATA,
}GAMEAPI_ERROR;


typedef enum GAMEAPI_World
{
	WORLD_FOREST = 0,
	WORLD_WINTER,
	WORLD_DESERT,
	WORLD_GRAVEYARD,
	WORLD_CANDYLAND,
	WORLD_COUNT,
}GAMEAPI_WORLD_TYPE;


typedef enum GAMEAPI_Animal
{
 ANIMAL_OWL,
 ANIMAL_PIG,
 ANIMAL_RAM,
 ANIMAL_DOG,
 ANIMAL_DUCK,
 ANIMAL_BEAR,
 ANIMAL_BULL,
 ANIMAL_LION,
 ANIMAL_MOUSE,
 ANIMAL_PANDA,
 ANIMAL_GOOSE,
 ANIMAL_HORSE,
 ANIMAL_KOALA,
 ANIMAL_SNAIL,
 ANIMAL_SNAKE,
 ANIMAL_SHEEP,
 ANIMAL_BEAVER,
 ANIMAL_COYOTE,
 ANIMAL_PARROT,
 ANIMAL_PIGEON,
 ANIMAL_RABBIT,
 ANIMAL_TURTLE,
 ANIMAL_CHEETAH,
 ANIMAL_CHICKEN,
 ANIMAL_LADYBUG,
 ANIMAL_KANGAROO,
 ANIMAL_SEATURTLE,
 ANIMAL_CROCODILE,
 ANIMAL_CATERPILLAR,
 ANIMAL_HIPPOPOTAMUS,
 ANIMAL_COUNT,
 ANIMAL_NULL
}GAMEAPI_ANIMAL;



#ifdef __ANDROID__


#define GAMEAPI_DATA_PATH "/"
#define GAMEAPI_ANIMALS_PATH "animals/"
#define GAMEAPI_FONT_PATH "font.ttf"
#define GAMEAPI_BALLOON_PATH_BLUE "blue"
#define GAMEAPI_BALLOON_PATH_GREEN "green"
#define GAMEAPI_BALLOON_PATH_ORANGE "orange"
#define GAMEAPI_BALLOON_PATH_PINK "pink"
#define GAMEAPI_BALLOON_PATH_PURPLE "purple"
#define GAMEAPI_BALLOON_PATH_RED "red"
#define GAMEAPI_BALLOON_PATH_YELLOW "yellow"


// UI
#define GAMEAPI_TEX_UI_PANEL_GREEN "ui/ui_panel_green.png"
#define GAMEAPI_TEX_BTN_FOREST_SELECT "ui/btn_forest_select.png"
#define GAMEAPI_TEX_BTN_WINTER_SELECT "ui/btn_winter_select.png"
#define GAMEAPI_TEX_BTN_DESERT_SELECT "ui/btn_desert_select.png"
#define GAMEAPI_TEX_BTN_GRAVEYARD_SELECT "ui/btn_grave_select.png"
#define GAMEAPI_TEX_BTN_CANDYLAND_SELECT "ui/btn_candy_select.png"


#define GAMEAPI_TEX_UI_PANEL_GREEN_UP "ui/ui_panel_green_up.png"
#define GAMEAPI_TEX_UI_YELLOW_UP "ui/ui_panel_yellow_up.png"
#define GAMEAPI_TEX_UI_RED_UP "ui/ui_panel_red_up.png"
#define GAMEAPI_TEX_UI_BLUE_UP "ui/ui_panel_blue_up.png"

#define GAMEAPI_TEX_UI_GREEN_DOWN "ui/ui_panel_green_down.png"
#define GAMEAPI_TEX_UI_YELLOW_DOWN "ui/ui_panel_yellow_down.png"
#define GAMEAPI_TEX_UI_RED_DOWN "ui/ui_panel_red_down.png"
#define GAMEAPI_TEX_UI_BLUE_DOWN "ui/ui_panel_blue_down.png"

#define GAMEAPI_TEX_UI_PANEL_MSG_BLUE "ui/ui_panel_msg_blue.png"

#define GAMEAPI_TEX_UI_PAUSE_UP "ui/ui_panel_pause.png"
#define GAMEAPI_TEX_UI_BACK "ui/ui_panel_back.png"

#define GAMEAPI_TEX_UI_PANEL_GRAY "ui/ui_panel_gray_window.png"
#define GAMEAPI_TEX_UI_TEXTBAR_PANEL_GRAY "ui/ui_textbar_panel.png"

//#define GAMEAPI_TEX_UI_PANEL_FOREST_FRAME "data/ui/forest_frame.png"
#define GAMEAPI_TEX_UI_PANEL_FOREST_FRAME "ui/forest_frame.png"
#define GAMEAPI_TEX_UI_PANEL_WINTER_FRAME "ui/winter_frame.png"

#define GAMEAPI_TEX_UI_PANEL_FOREST_FRAME_COLLECTION "ui/forest_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_WINTER_FRAME_COLLECTION "ui/winter_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_DESERT_FRAME_COLLECTION "ui/desert_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_GRAVE_FRAME_COLLECTION "ui/grave_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_CANDY_FRAME_COLLECTION "ui/candy_frame_collection.png"

#define GAMEAPI_TEX_UI_ARROW_LEFT "ui/ui_arrow_left.png"
#define GAMEAPI_TEX_UI_ARROW_RIGHT "ui/ui_arrow_right.png"

#define GAMEAPI_TEX_BALLOON_UNKNOWN "uncollected.png"
#define GAMEAPI_TEX_STAR_GRAY "star_gray.png"


#define GAMEAPI_TEX_ANIMAL_FROG "animals/frog.png"
#define GAMEAPI_TEX_ANIMAL_TURTLE "animals/turtle.png"
#define GAMEAPI_TEX_ANIMAL_HEDGE "animals/hedgehog.png"
#define GAMEAPI_TEX_ANIMAL_RABBUT "animals/rabbit.png"
#define GAMEAPI_TEX_ANIMAL_SNAIL  "animals/snail.png"
#define GAMEAPI_TEX_ANIMAL_DEER  "animals/deer.png"


#define GAMEAPI_TEX_FOREST_PARALAX1 "world1/px_bck/layer_01.png"
#define GAMEAPI_TEX_FOREST_PARALAX2 "world1/px_bck/layer_02.png"
#define GAMEAPI_TEX_FOREST_PARALAX3 "world1/px_bck/layer_03.png"
#define GAMEAPI_TEX_FOREST_PARALAX4 "world1/px_bck/layer_04.png"
#define GAMEAPI_TEX_FOREST_PARALAX5 "world1/px_bck/layer_05.png"

#define GAMEAPI_TEX_WINTER_PARALAX1 "world2/px_bck/layer_01.png"
#define GAMEAPI_TEX_WINTER_PARALAX2 "world2/px_bck/layer_02.png"
#define GAMEAPI_TEX_WINTER_PARALAX3 "world2/px_bck/layer_03.png"
#define GAMEAPI_TEX_WINTER_PARALAX4 "world2/px_bck/layer_04.png"
#define GAMEAPI_TEX_WINTER_PARALAX5 "world2/px_bck/layer_05.png"

#define GAMEAPI_TEX_DESERT_PARALAX1 "world3/px_bck/layer_01.png"
#define GAMEAPI_TEX_DESERT_PARALAX2 "world3/px_bck/layer_02.png"
#define GAMEAPI_TEX_DESERT_PARALAX3 "world3/px_bck/layer_03.png"
#define GAMEAPI_TEX_DESERT_PARALAX4 "world3/px_bck/layer_04.png"
#define GAMEAPI_TEX_DESERT_PARALAX5 "world3/px_bck/layer_05.png"

#define GAMEAPI_TEX_GRAVE_PARALAX1 "world4/px_bck/layer_01.png"
#define GAMEAPI_TEX_GRAVE_PARALAX2 "world4/px_bck/layer_02.png"
#define GAMEAPI_TEX_GRAVE_PARALAX3 "world4/px_bck/layer_03.png"
#define GAMEAPI_TEX_GRAVE_PARALAX4 "world4/px_bck/layer_04.png"
#define GAMEAPI_TEX_GRAVE_PARALAX5 "world4/px_bck/layer_05.png"

#define GAMEAPI_TEX_CANDY_PARALAX1 "world5/px_bck/layer_01.png"
#define GAMEAPI_TEX_CANDY_PARALAX2 "world5/px_bck/layer_02.png"
#define GAMEAPI_TEX_CANDY_PARALAX3 "world5/px_bck/layer_03.png"
#define GAMEAPI_TEX_CANDY_PARALAX4 "world5/px_bck/layer_04.png"
#define GAMEAPI_TEX_CANDY_PARALAX5 "world5/px_bck/layer_05.png"



#define GAMEAPI_TEX_FIREST_LEVEL_MARKER "world1/pointer.png"
#define GAMEAPI_TEX_WINTER_LEVEL_MARKER "world2/pointer.png"
#define GAMEAPI_TEX_DESERT_LEVEL_MARKER "world3/pointer.png"
#define GAMEAPI_TEX_GRAVE_LEVEL_MARKER "world4/pointer.png"
#define GAMEAPI_TEX_CANDY_LEVEL_MARKER "world5/pointer.png"

#define GAMEAPI_TEX_STAR0 "stars_0.png" // sve sive
#define GAMEAPI_TEX_STAR1 "stars_1.png"
#define GAMEAPI_TEX_STAR2 "stars_2.png"
#define GAMEAPI_TEX_STAR3 "stars_3.png"

#define GAMEAPI_TEX_FOREST_RAW "button_forest_raw.png"
#define GAMEAPI_TEX_WINTER_RAW "button_winter_raw.png"
#define GAMEAPI_TEX_DESERT_RAW "button_desert_raw.png"
#define GAMEAPI_TEX_GRAVE_RAW "button_grave_raw.png"
#define GAMEAPI_TEX_CANDY_RAW "button_candy_raw.png"




#define GAMEAPI_TEX_BTN_FOREST_LEVEL "world1/level.png"
#define GAMEAPI_TEX_BTN_WINTER_LEVEL "world2/level.png"
#define GAMEAPI_TEX_BTN_DESERT_LEVEL "world3/level.png"
#define GAMEAPI_TEX_BTN_GRAVEYARD_LEVEL "world4/level.png"
#define GAMEAPI_TEX_BTN_CANDYLAND_LEVEL "world5/level.png"

#define GAMEAPI_TEX_STAR "Star.png"


#define GAMEAPI_TEX_YELLOW_PANEL "yellow_button00.png"
#define GAMEAPI_TEX_RED_PANEL "red_button00.png"
#define GAMEAPI_TEX_RED_PANEL_WIDE "red_panel_wide.png"

#define GAMEAPI_TEX_LIFE "hearth.png"


#define GAMEAPI_TEX_BACK_MENU_PANEL "menu_back.png"



#define GAMEAPI_TEX_WORLD_FOREST "world1/background.png"
#define GAMEAPI_TEX_WORLD_WINTER "world2/background.png"
#define GAMEAPI_TEX_WORLD_DESERT "world3/background.png"
#define GAMEAPI_TEX_WORLD_GRAVEYARD "world4/background.png"
#define GAMEAPI_TEX_WORLD_CANDYLAND "world5/background.png"


//#define GAMEAPI_TEX_LEVEL1_BACK "data/bg1/level_background.png"
//#define GAMEAPI_TEX_LEVEL2_BACK "data/bg2/level_background.png"

#define GAMEAPI_TEX_LEVEL1_BACK "ui/forest.png"
#define GAMEAPI_TEX_LEVEL2_BACK "ui/winter.png"
#define GAMEAPI_TEX_LEVEL3_BACK "ui/desert.png"
#define GAMEAPI_TEX_LEVEL4_BACK "ui/grave.png"
#define GAMEAPI_TEX_LEVEL5_BACK "ui/candy.png"

#define GAMEAPI_TEX_STAT_FRAME "ui/stat_frame.png"

#define GAMEAPI_TEX_GREEN_FRAME "ui/gold_frame.png"
#define GAMEAPI_TEX_WHITE_FRAME "ui/white_frame.png"
#define GAMEAPI_TEX_GOLD_FRAME "ui/gold_frame.png"


#define GAMEAPI_TEX_ANIMAL_FRAME "ui/animal_frame_empty.png"
#define GAMEAPI_TEX_ANIMAL_FRAMEQ "ui/animal_frame_q.png"


#define GAMEAPI_TEX_TODO "TODO.png"

#define GAMEAPI_BALLOON_MISSED "missed.png"
#define GAMEAPI_LETTER_MISSED "lettermiss.png"


#define GAMEAPI_TEX_BACK_TO_GAME "ui/back_to_game.png"
#define GAMEAPI_TEX_SPLASH "logo.png"

#define GAMEAPI_TEX_ARROW_CONTINUE "ui/fingerpoint.png"


#define GAMEAPI_TEX_GEARS "ui/gears.png"

#define GAMEAPI_TEX_DOOR_EXIT "ui/door_exit.png"


#define GAMEAPI_MUSIC_ON_PATH "ui/music_on.png"
#define GAMEAPI_MUSIC_OFF_PATH "ui/music_off.png"



#define GAMEAPI_SFX_ON_PATH "ui/sfx_on.png"
#define GAMEAPI_SFX_OFF_PATH "ui/sfx_off.png"




//
//#define GAMEAPI_SOUND_POP "sound/pop.ogg"
//#define GAMEAPI_SOUND_CORRECT "sound/letter_correct.ogg"
//#define GAMEAPI_SOUND_MISS "sound/miss.wav"
//#define GAMEAPI_SOUND_FOREST_BK "sound/forest_background.ogg"
//#define GAMEAPI_SOUND_WINTER_BK "sound/winter_background.ogg"
//#define GAMEAPI_SOUND_GRAVE_BK "sound/graveyard_background.ogg"
//#define GAMEAPI_SOUND_FOREST_MUSIC "sound/forest_music.ogg"
//#define GAMEAPI_SOUND_WINTER_MUSIC "sound/winter_music.ogg"
//#define GAMEAPI_SOUND_GRAVE_MUSIC "sound/grave_music.ogg"
//#define GAMEAPI_SOUND_DESERT_MUSIC "sound/desert_music.ogg"
//#define GAMEAPI_SOUND_CANDY_MUSIC "sound/candy_music.ogg"
//#define GAMEAPI_SOUND_MAIN_MUSIC "sound/main_menu.ogg"


#define GAMEAPI_SOUND_POP "sound/pop.ogg"
#define GAMEAPI_SOUND_CORRECT "sound/letter_correct.ogg"
#define GAMEAPI_SOUND_MISS "sound/miss.ogg"
#define GAMEAPI_SOUND_FOREST_BK "sound/forest_background.ogg"
#define GAMEAPI_SOUND_WINTER_BK "sound/winter_background.ogg"
#define GAMEAPI_SOUND_GRAVE_BK "sound/graveyard_background.ogg"
#define GAMEAPI_SOUND_FOREST_MUSIC "sound/forest_music.ogg"
#define GAMEAPI_SOUND_WINTER_MUSIC "sound/winter_music.ogg"
#define GAMEAPI_SOUND_GRAVE_MUSIC "sound/grave_music.ogg"
#define GAMEAPI_SOUND_DESERT_MUSIC "sound/desert_music.ogg"
#define GAMEAPI_SOUND_CANDY_MUSIC "sound/candy_music.ogg"

#define GAMEAPI_SOUND_WINNER_MUSIC "sound/winner.wav"
#define GAMEAPI_SOUND_MAIN_MUSIC "sound/main_menu.ogg"




#define GAMEAPI_GAMEDATA_PATH "gamedata.sys"
#define  GAMEAPI_ANIMALSDATA_PATH "animals.dat"
#define GAMEAPI_POP_PATH "pop.txt"


#else 



#define GAMEAPI_DATA_PATH "data/"
#define GAMEAPI_ANIMALS_PATH "data/animals"
#define GAMEAPI_FONT_PATH "data/font.ttf"
#define GAMEAPI_BALLOON_PATH_BLUE "data/blue/"
#define GAMEAPI_BALLOON_PATH_GREEN "data/green/"
#define GAMEAPI_BALLOON_PATH_ORANGE "data/orange/"
#define GAMEAPI_BALLOON_PATH_PINK "data/pink/"
#define GAMEAPI_BALLOON_PATH_PURPLE "data/purple/"
#define GAMEAPI_BALLOON_PATH_RED "data/red/"
#define GAMEAPI_BALLOON_PATH_YELLOW "data/yellow/"


// UI
#define GAMEAPI_TEX_UI_PANEL_GREEN "data/ui/ui_panel_green.png"
#define GAMEAPI_TEX_BTN_FOREST_SELECT "data/ui/btn_forest_select.png"
#define GAMEAPI_TEX_BTN_WINTER_SELECT "data/ui/btn_winter_select.png"
#define GAMEAPI_TEX_BTN_DESERT_SELECT "data/ui/btn_desert_select.png"
#define GAMEAPI_TEX_BTN_GRAVEYARD_SELECT "data/ui/btn_grave_select.png"
#define GAMEAPI_TEX_BTN_CANDYLAND_SELECT "data/ui/btn_candy_select.png"




#define GAMEAPI_TEX_UI_PANEL_GREEN_UP "data/ui/ui_panel_green_up.png"
#define GAMEAPI_TEX_UI_YELLOW_UP "data/ui/ui_panel_yellow_up.png"
#define GAMEAPI_TEX_UI_RED_UP "data/ui/ui_panel_red_up.png"
#define GAMEAPI_TEX_UI_BLUE_UP "data/ui/ui_panel_blue_up.png"

#define GAMEAPI_TEX_UI_GREEN_DOWN "data/ui/ui_panel_green_down.png"
#define GAMEAPI_TEX_UI_YELLOW_DOWN "data/ui/ui_panel_yellow_down.png"
#define GAMEAPI_TEX_UI_RED_DOWN "data/ui/ui_panel_red_down.png"
#define GAMEAPI_TEX_UI_BLUE_DOWN "data/ui/ui_panel_blue_down.png"
#define GAMEAPI_TEX_UI_PANEL_MSG_BLUE "data/ui/ui_panel_msg_blue.png"


#define GAMEAPI_TEX_UI_PAUSE_UP "data/ui/ui_panel_pause.png"
#define GAMEAPI_TEX_UI_BACK "data/ui/ui_panel_back.png"

#define GAMEAPI_TEX_UI_PANEL_GRAY "data/ui/ui_panel_gray_window.png"
#define GAMEAPI_TEX_UI_TEXTBAR_PANEL_GRAY "data/ui/ui_textbar_panel.png"


//#define GAMEAPI_TEX_UI_PANEL_FOREST_FRAME "data/ui/forest_frame.png"
#define GAMEAPI_TEX_UI_PANEL_FOREST_FRAME "data/ui/forest_frame.png"
#define GAMEAPI_TEX_UI_PANEL_WINTER_FRAME "data/ui/winter_frame.png"

#define GAMEAPI_TEX_UI_PANEL_FOREST_FRAME_COLLECTION "data/ui/forest_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_WINTER_FRAME_COLLECTION "data/ui/winter_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_DESERT_FRAME_COLLECTION "data/ui/desert_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_GRAVE_FRAME_COLLECTION "data/ui/grave_frame_collection.png"
#define GAMEAPI_TEX_UI_PANEL_CANDY_FRAME_COLLECTION "data/ui/candy_frame_collection.png"

#define GAMEAPI_TEX_UI_ARROW_LEFT "data/ui/ui_arrow_left.png"
#define GAMEAPI_TEX_UI_ARROW_RIGHT "data/ui/ui_arrow_right.png"

#define GAMEAPI_TEX_BALLOON_UNKNOWN "data/uncollected.png"
#define GAMEAPI_TEX_STAR_GRAY "data/star_gray.png"


#define GAMEAPI_TEX_ANIMAL_FROG "data/animals/frog.png"
#define GAMEAPI_TEX_ANIMAL_TURTLE "data/animals/turtle.png"
#define GAMEAPI_TEX_ANIMAL_HEDGE "data/animals/hedgehog.png"
#define GAMEAPI_TEX_ANIMAL_RABBUT "data/animals/rabbit.png"
#define GAMEAPI_TEX_ANIMAL_SNAIL  "data/animals/snail.png"
#define GAMEAPI_TEX_ANIMAL_DEER  "data/animals/deer.png"


#define GAMEAPI_TEX_FOREST_PARALAX1 "data/bg1/px_bck/layer_01.png"
#define GAMEAPI_TEX_FOREST_PARALAX2 "data/bg1/px_bck/layer_02.png"
#define GAMEAPI_TEX_FOREST_PARALAX3 "data/bg1/px_bck/layer_03.png"
#define GAMEAPI_TEX_FOREST_PARALAX4 "data/bg1/px_bck/layer_04.png"
#define GAMEAPI_TEX_FOREST_PARALAX5 "data/bg1/px_bck/layer_05.png"

#define GAMEAPI_TEX_WINTER_PARALAX1 "data/bg2/px_bck/layer_01.png"
#define GAMEAPI_TEX_WINTER_PARALAX2 "data/bg2/px_bck/layer_02.png"
#define GAMEAPI_TEX_WINTER_PARALAX3 "data/bg2/px_bck/layer_03.png"
#define GAMEAPI_TEX_WINTER_PARALAX4 "data/bg2/px_bck/layer_04.png"
#define GAMEAPI_TEX_WINTER_PARALAX5 "data/bg2/px_bck/layer_05.png"

#define GAMEAPI_TEX_DESERT_PARALAX1 "data/bg3/px_bck/layer_01.png"
#define GAMEAPI_TEX_DESERT_PARALAX2 "data/bg3/px_bck/layer_02.png"
#define GAMEAPI_TEX_DESERT_PARALAX3 "data/bg3/px_bck/layer_03.png"
#define GAMEAPI_TEX_DESERT_PARALAX4 "data/bg3/px_bck/layer_04.png"
#define GAMEAPI_TEX_DESERT_PARALAX5 "data/bg3/px_bck/layer_05.png"

#define GAMEAPI_TEX_GRAVE_PARALAX1 "data/bg4/px_bck/layer_01.png"
#define GAMEAPI_TEX_GRAVE_PARALAX2 "data/bg4/px_bck/layer_02.png"
#define GAMEAPI_TEX_GRAVE_PARALAX3 "data/bg4/px_bck/layer_03.png"
#define GAMEAPI_TEX_GRAVE_PARALAX4 "data/bg4/px_bck/layer_04.png"
#define GAMEAPI_TEX_GRAVE_PARALAX5 "data/bg4/px_bck/layer_05.png"

#define GAMEAPI_TEX_CANDY_PARALAX1 "data/bg5/px_bck/layer_01.png"
#define GAMEAPI_TEX_CANDY_PARALAX2 "data/bg5/px_bck/layer_02.png"
#define GAMEAPI_TEX_CANDY_PARALAX3 "data/bg5/px_bck/layer_03.png"
#define GAMEAPI_TEX_CANDY_PARALAX4 "data/bg5/px_bck/layer_04.png"
#define GAMEAPI_TEX_CANDY_PARALAX5 "data/bg5/px_bck/layer_05.png"



#define GAMEAPI_TEX_FIREST_LEVEL_MARKER "data/bg1/pointer.png"
#define GAMEAPI_TEX_WINTER_LEVEL_MARKER "data/bg2/pointer.png"
#define GAMEAPI_TEX_DESERT_LEVEL_MARKER "data/bg3/pointer.png"
#define GAMEAPI_TEX_GRAVE_LEVEL_MARKER "data/bg4/pointer.png"
#define GAMEAPI_TEX_CANDY_LEVEL_MARKER "data/bg5/pointer.png"

#define GAMEAPI_TEX_STAR0 "data/stars_0.png"
#define GAMEAPI_TEX_STAR1 "data/stars_1.png"
#define GAMEAPI_TEX_STAR2 "data/stars_2.png"
#define GAMEAPI_TEX_STAR3 "data/stars_3.png"

#define GAMEAPI_TEX_FOREST_RAW "data/button_forest_raw.png"
#define GAMEAPI_TEX_WINTER_RAW "data/button_winter_raw.png"
#define GAMEAPI_TEX_DESERT_RAW "data/button_desert_raw.png"
#define GAMEAPI_TEX_GRAVE_RAW "data/button_grave_raw.png"
#define GAMEAPI_TEX_CANDY_RAW "data/button_candy_raw.png"




#define GAMEAPI_TEX_BTN_FOREST_LEVEL "data/bg1/level.png"
#define GAMEAPI_TEX_BTN_WINTER_LEVEL "data/bg2/level.png"
#define GAMEAPI_TEX_BTN_DESERT_LEVEL "data/bg3/level.png"
#define GAMEAPI_TEX_BTN_GRAVEYARD_LEVEL "data/bg4/level.png"
#define GAMEAPI_TEX_BTN_CANDYLAND_LEVEL "data/bg5/level.png"

#define GAMEAPI_TEX_STAR "data/star.png"


#define GAMEAPI_TEX_YELLOW_PANEL "data/yellow_button00.png"
#define GAMEAPI_TEX_RED_PANEL "data/red_button00.png"
#define GAMEAPI_TEX_RED_PANEL_WIDE "data/red_panel_wide.png"

#define GAMEAPI_TEX_LIFE "data/hearth.png"


#define GAMEAPI_TEX_BACK_MENU_PANEL "data/menu_back.png"



#define GAMEAPI_TEX_WORLD_FOREST "data/bg1/background.png"
#define GAMEAPI_TEX_WORLD_WINTER "data/bg2/background.png"
#define GAMEAPI_TEX_WORLD_DESERT "data/bg3/background.png"
#define GAMEAPI_TEX_WORLD_GRAVEYARD "data/bg4/background.png"
#define GAMEAPI_TEX_WORLD_CANDYLAND "data/bg5/background.png"


//#define GAMEAPI_TEX_LEVEL1_BACK "data/bg1/level_background.png"
//#define GAMEAPI_TEX_LEVEL2_BACK "data/bg2/level_background.png"

#define GAMEAPI_TEX_LEVEL1_BACK "data/ui/forest.png"
#define GAMEAPI_TEX_LEVEL2_BACK "data/ui/winter.png"
#define GAMEAPI_TEX_LEVEL3_BACK "data/ui/desert.png"
#define GAMEAPI_TEX_LEVEL4_BACK "data/ui/grave.png"
#define GAMEAPI_TEX_LEVEL5_BACK "data/ui/candy.png"

#define GAMEAPI_TEX_STAT_FRAME "data/ui/stat_frame.png"

#define GAMEAPI_TEX_GREEN_FRAME "data/ui/gold_frame.png"
#define GAMEAPI_TEX_WHITE_FRAME "data/ui/white_frame.png"
#define GAMEAPI_TEX_GOLD_FRAME "data/ui/gold_frame.png"


#define GAMEAPI_TEX_ANIMAL_FRAME "data/ui/animal_frame_empty.png"
#define GAMEAPI_TEX_ANIMAL_FRAMEQ "data/ui/animal_frame_q.png"

#define GAMEAPI_TEX_TODO "data/TODO.png"


#define GAMEAPI_BALLOON_MISSED "data/missed.png"
#define GAMEAPI_LETTER_MISSED "data/lettermiss.png"


#define GAMEAPI_TEX_GEARS "data/gears.png"

#define GAMEAPI_TEX_DOOR_EXIT "data/door_exit.png"

#define GAMEAPI_TEX_BACK_TO_GAME "data/ui/back_to_game.png"
#define GAMEAPI_TEX_SPLASH "data/logo.png"
#define GAMEAPI_TEX_LOADING "data/loading.png"

#define GAMEAPI_TEX_ARROW_CONTINUE "data/ui/fingerpoint.png"



#define  GAMEAPI_GAMEDATA_PATH "data/gamedata.sys"
#define  GAMEAPI_ANIMALSDATA_PATH "data/animals.dat"


#define GAMEAPI_MUSIC_ON_PATH "data/ui/music_on.png"
#define GAMEAPI_MUSIC_OFF_PATH "data/ui/music_off.png"



#define GAMEAPI_SFX_ON_PATH "data/ui/sfx_on.png"
#define GAMEAPI_SFX_OFF_PATH "data/ui/sfx_off.png"


#define GAMEAPI_POP_PATH "pop.txt"


#endif


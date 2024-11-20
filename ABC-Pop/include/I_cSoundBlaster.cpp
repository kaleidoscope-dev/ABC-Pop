#include "gameapi.h"
#include "I_cSoundBlaster.h"
#include "I_cGameData.h"

I_cSoundBlaster::I_cSoundBlaster()
{

}


I_cSoundBlaster::~I_cSoundBlaster()
{ 


}




void I_cSoundBlaster::PlayPop()
{
 if (gGameData.sfx_on_)
	   Mix_PlayChannel(CHANNEL_SFX, gAssetManager->GetSound_Pop(), 0);
}




void I_cSoundBlaster::PlayLetterHit(void)
{
	if (gGameData.sfx_on_)
		 Mix_PlayChannel(CHANNEL_SFX, gAssetManager->GetSound_LetterHit(), 0);
}

void I_cSoundBlaster::PlayLetterMiss(void)
{
	if (gGameData.sfx_on_)
		Mix_PlayChannel(CHANNEL_SFX, gAssetManager->GetSound_LetterMiss(), 0);

}


void I_cSoundBlaster::PlayForestBackground(void)
{
	if (gGameData.sfx_on_)
		 Mix_PlayChannel(CHANNEL_BACKGROUND,gAssetManager->GetSound_ForestBackground(), -1);
}


void I_cSoundBlaster::PlayWinterBackground(void)
{
	if (gGameData.sfx_on_)
		 Mix_PlayChannel(CHANNEL_BACKGROUND,gAssetManager->GetSound_WinterBackground(), -1);
}


void I_cSoundBlaster::PlayGraveBackground(void)
{
	if (gGameData.sfx_on_)
	    Mix_PlayChannel(CHANNEL_BACKGROUND, gAssetManager->GetSound_GraveBackground(), -1);
}


void I_cSoundBlaster::PlayMainMenu(void)
{
	if (gGameData.music_on_ && playing_music_ == false)
	   {
        Mix_PlayMusic(gAssetManager->GetMusic_MainMenu(),-1);
			Mix_FadeInMusic(gAssetManager->GetMusic_MainMenu(), -1,800);
			playing_music_ = true;
		 }
}


void I_cSoundBlaster::PlayForestMusic(void)
{
	if (gGameData.music_on_  && playing_music_ == false)
	   {
	    Mix_PlayMusic(gAssetManager->GetMusic_Forest(), -1);
			Mix_FadeInMusic(gAssetManager->GetMusic_Forest(), -1, 800);
			playing_music_ = true;
		 }

}

void I_cSoundBlaster::PlayWinterMusic(void)
{
	if (gGameData.music_on_ &&  playing_music_ == false)
	   {
      Mix_PlayMusic(gAssetManager->GetMusic_Winter(),-1);
			Mix_FadeInMusic(gAssetManager->GetMusic_Winter(), -1, 800);
			playing_music_ = true;
		 }
}


void I_cSoundBlaster::PlayGraveMusic(void)
{
	if (gGameData.music_on_ && playing_music_ == false)
	   {
	    Mix_PlayMusic(gAssetManager->GetMusic_Graveyard(), -1);
			Mix_FadeInMusic(gAssetManager->GetMusic_Graveyard(), -1, 800);
			playing_music_ = true;
		 }
}



void I_cSoundBlaster::PlayDesertMusic(void)
{
	if (gGameData.music_on_ && playing_music_ == false)
	{
	 Mix_PlayMusic(gAssetManager->GetMusic_Desert(), -1);
	 Mix_FadeInMusic(gAssetManager->GetMusic_Desert(), -1, 800);
	 playing_music_ = true;
	}
}

void I_cSoundBlaster::PlayCandyMusic(void)
{
	if (gGameData.music_on_ && playing_music_ == false)
	   {
	    Mix_PlayMusic(gAssetManager->GetMusic_Candy(), -1);
			Mix_FadeInMusic(gAssetManager->GetMusic_Candy(), -1, 800);
			playing_music_ = true;
	}
}


void I_cSoundBlaster::PlayWinnerMusic(void)
{
	if (gGameData.music_on_ && playing_music_ == false)
	   {
	    Mix_PlayMusic(gAssetManager->GetMusic_Winner(), -1);
			Mix_FadeInMusic(gAssetManager->GetMusic_Winner(), -1, 800);
			playing_music_ = true;
	   } 
}


void I_cSoundBlaster::StopMusic(void)
{
 playing_music_ = false;
 Mix_FadeOutMusic(800);
}


void I_cSoundBlaster::StopChannel(int channel)
{
 Mix_HaltChannel(channel);
}





void I_cSoundBlaster::MusicOff(void)
{
	Mix_HaltMusic();
   playing_music_ = false;
}


void I_cSoundBlaster::SfxOff(void)
{
 //StopChannel(0);
 //StopChannel(1);
 //StopChannel(2);
}



void I_cSoundBlaster::StopAll(void)
{
	StopChannel(0);
	StopChannel(1);
	StopChannel(2);
	
	StopMusic();
	

}



void I_cSoundBlaster::PlayDesertBackground(void)
{
   if (gGameData.sfx_on_)
      Mix_PlayChannel(CHANNEL_BACKGROUND, gAssetManager->GetSound_WinterBackground(), -1);
}


void I_cSoundBlaster::PlayCandyBackground(void)
{
   if (gGameData.sfx_on_)
      Mix_PlayChannel(CHANNEL_BACKGROUND, gAssetManager->GetSound_ForestBackground(), -1);
}

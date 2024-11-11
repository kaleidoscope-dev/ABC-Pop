#pragma once
#include "I_cAssetmanager.h"




class I_cSoundBlaster
{
public:
	   I_cSoundBlaster();
	  ~I_cSoundBlaster();


	  
		void PlayPop(void);
    void PlayLetterHit(void);
		void PlayLetterMiss(void);
		void PlayForestBackground(void);
		void PlayWinterBackground(void);
		void PlayGraveBackground(void);
		void PlayDesertBackground(void);
		void PlayCandyBackground(void);
		void PlayMainMenu(void);
		void PlayForestMusic(void);
		void PlayWinterMusic(void);
		void PlayGraveMusic(void);
		void PlayDesertMusic(void);
		void PlayCandyMusic(void);
        void PlayWinnerMusic(void);

		void StopMusic(void);
		void StopChannel(int channel);

		void MusicOff(void);
		void SfxOff(void);


		void StopAll(void);


 private:
    bool playing_music_;
		
};

extern I_cSoundBlaster gSoundBlaster;
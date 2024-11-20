#pragma once
#include "gameapi.h"


class I_cGameData
{
	public:
		I_cGameData();
	   ~I_cGameData();

	   int LoadGameData(void);

	   int SaveGameData(void);

		 void SetCurrentLevel(int l);
		 void SetCurrentWorld(int w);

	   int GetCurrentLevel();
		 int GetCurrentWorld();

		 int GetStarCount(int w, int l);
		 void SetLevelFinished(int starcnt);
		 
		 int NextLevel(void);
		 void ResetLevel(void);
		 void NextWorld(void);
		 void ResetWorld(void);



		 int GetLastFinishedLevel(int world);
		 int GetLastFinishedWorld(void);
		 void ChangeGamePhase(void);


	   bool IsWorldFinished(int world);
	   bool IsInProgress(int world);
	   void SetWorldFinished(int world);
	   void SetInProgress(int world, bool p);

		 bool IsLevelFinished(int world, int level);

	   void ResetGameData(void);

		 bool IsGameOver(void);

		 void UpdateBalloonsMissed(void);
		 void UpdateBalloonsPop(void);
		 void UpdateLettersMissed(void);

		 void ResetCounters(void);


		 void SetAnimalCollected(int world, int level,  int num);
		 bool IsAnimalCollected(int world, int level, int num);

		 //bool IsCollected(int world, int level, int ani_num);

	   GAMEAPI_WORLD_DATA worldData_[WORLD_COUNT];

		 GAMEAPI_ANIMAL GetLevelAnimal(int world, int level, int num);


		 int balloons_pop_;
		 int balloons_miss_;
		 int letter_miss_;

		 bool sfx_on_;
		 bool music_on_;
private:
		 int current_world_;
		 int currentLevel_;

         int SaveGameDataRW(void);
         int LoadGameDataRW(void);
         int LoadGameDataPC(void);
         int SaveGameDataPC(void);


};


extern I_cGameData gGameData;
#include "I_cGameData.h"
#include "I_cLog.h"


I_cGameData gGameData;

I_cGameData::I_cGameData()
{
 sfx_on_ = true;
 music_on_ = true;
}


I_cGameData::~I_cGameData()
{
}





//==============================================================================================//
//=====================[ SAVE GAME DATA ]=======================================================//
//==============================================================================================//
int I_cGameData::LoadGameData(void)
{
    int err = 0;
#ifdef __ANDROID__
    err = LoadGameDataRW();
#else
    err = LoadGameDataPC();
#endif
    return err;
}

int I_cGameData::SaveGameData(void)
{
    int err = 0;
#ifdef __ANDROID__
    err = SaveGameDataRW();
#else
    err = SaveGameDataPC();
#endif

    return err;
}



int I_cGameData::SaveGameDataPC(void)
{
	int len = 0;
	vector<uint8_t>vbuffer;

	FILE *f = fopen(GAMEAPI_GAMEDATA_PATH, "wb");
	if (f)
	{
		vbuffer.push_back(GAMEAPI_Phase_);  // phase

		for (int c = 0; c < WORLD_COUNT; c++)
		{
			vbuffer.push_back(c);  // world 
			vbuffer.push_back(worldData_[c].in_progress);  // finished
			vbuffer.push_back(worldData_[c].finished);  // finished

			for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
			{
				vbuffer.push_back(worldData_[c].levelData[i].finished); // finished
				vbuffer.push_back(worldData_[c].levelData[i].star_num); // star num
				vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.animal1); // animals
				vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.collected1); // animals
				vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.animal2); // animals
				vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.collected2); // animals
			}
		}

		// unlocked ballones
		uint8_t *write_buf = new uint8_t[vbuffer.size()];
		for (int c = 0; c < vbuffer.size(); c++)
		{
			write_buf[c] = vbuffer[c];
		}

		fwrite(write_buf, vbuffer.size(), 1, f);


		delete []write_buf;
		fclose(f);
	}

	return 0;

}


int I_cGameData::SaveGameDataRW(void)
{
    int len = 0;
    vector<uint8_t>vbuffer;

    SDL_RWops* rw = SDL_RWFromFile("gamedata.sys", "wb");
    if (rw == NULL) return NULL;

    if (rw)
       {
        vbuffer.push_back(GAMEAPI_Phase_);  // phase

        for (int c = 0; c < WORLD_COUNT; c++)
        {
            vbuffer.push_back(c);  // world 
            vbuffer.push_back(worldData_[c].in_progress);  // finished
            vbuffer.push_back(worldData_[c].finished);  // finished

            for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
            {
                vbuffer.push_back(worldData_[c].levelData[i].finished); // finished
                vbuffer.push_back(worldData_[c].levelData[i].star_num); // star num
                vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.animal1); // animals
                vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.collected1); // animals
                vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.animal2); // animals
                vbuffer.push_back((uint8_t)worldData_[c].levelData[i].animal.collected2); // animals
            }
        }

        // unlocked ballones
        int buf_size = vbuffer.size();

        uint8_t* write_buf = new uint8_t[vbuffer.size()];
        for (int c = 0; c < vbuffer.size(); c++)
        {
            write_buf[c] = vbuffer[c];
        }

        int write_size = SDL_RWwrite(rw, write_buf, 1, vbuffer.size());

		SDL_RWclose(rw);
       }



 return 0;
}



//==============================================================================================//
//=====================[ LOAD GAME DATA ]=======================================================//
// Check if gamedata exists, create new if not, close, open and load data
//==============================================================================================//
int I_cGameData::LoadGameDataRW(void)
{
    SDL_RWops* rw = SDL_RWFromFile("gamedata.sys", "rb");
    if (rw == NULL) return NULL;

    Sint64 res_size = SDL_RWsize(rw);
    uint8_t* buffer = (uint8_t*)malloc(res_size + 1);

    Sint64 nb_read_total = 0, nb_read = 1;
    uint8_t* buf = buffer;
    while (nb_read_total < res_size && nb_read != 0)
          {
           nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
           nb_read_total += nb_read;
           buf += nb_read;
          }

    SDL_RWclose(rw);

    if (nb_read_total != res_size) 
       {
        free(buffer);
        return NULL;
       }


	// again from the beggining
	int count = 0;
	GAMEAPI_Phase_ = buffer[count++];


	// load phase

	// Load data from buffer
	// for every world
	for (int c = 0; c < WORLD_COUNT; c++)
	{
		worldData_[c].world = buffer[count++];
		worldData_[c].in_progress = (bool)buffer[count++];
		worldData_[c].finished = (bool)buffer[count++];

		// for every level
		for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
		{
			worldData_[c].levelData[i].finished = buffer[count++];
			worldData_[c].levelData[i].star_num = buffer[count++];
			worldData_[c].levelData[i].animal.animal1 = (GAMEAPI_ANIMAL)buffer[count++];
			worldData_[c].levelData[i].animal.collected1 = (GAMEAPI_ANIMAL)buffer[count++];// deprecated
			worldData_[c].levelData[i].animal.animal2 = (GAMEAPI_ANIMAL)buffer[count++];// deprecated
			worldData_[c].levelData[i].animal.collected2 = (GAMEAPI_ANIMAL)buffer[count++];// deprecated


		}
	}

	// visualize
	//for (int c = 0; c < WORLD_COUNT; c++)
	//{
	//	for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
	//	{
	//		gLog->AppendLog("Worlddata[%d].leveldata[%d].finished = %d", c, i, worldData_[c].levelData[i].finished);
	//	}
	//}

	delete []buffer;
	current_world_ = GetLastFinishedWorld();
	currentLevel_ = GetLastFinishedLevel(current_world_);



	return 0;
}
//______________________________________________________________________________________________//




//==============================================================================================//
//=====================[ LOAD GAME DATA ]=======================================================//
// Check if gamedata exists, create new if not, close, open and load data
//==============================================================================================//
int I_cGameData::LoadGameDataPC(void)
{
	int len = 0;

	FILE *f = fopen("data/gamedata.sys", "rb");
	if (f == NULL)
		 {
			int len = 0;
			vector<uint8_t>vbuffer;

			f = fopen(GAMEAPI_GAMEDATA_PATH, "wb");  // create new gamedata

			// create new game data
			if (!f)
				return -1; //ERROR: unable eto create file
		
		
			ResetGameData();  // reset the savefile
            SaveGameDataPC();


			return 0; // we don't need anything here anymore. We can safely return.
		 }

    // from the beggining now, how many bytes we read
		fseek(f, 0, SEEK_END);

		// size of read_bytes
		size_t size = ftell(f);
		if (size == 0)
		   {
			  fclose(f);
			  return -1;
		   }
		
		// Ok, back to start
		rewind(f);

		// read the size bytes into buffer and close the file
	  uint8_t *buffer = new uint8_t[size];
	  fread(buffer, 1, size, f); 
	  fclose(f);

		// again from the beggining
	  int count = 0;
		GAMEAPI_Phase_ = buffer[count++];


		// load phase

    // Load data from buffer  
	  // for every world
	  for (int c = 0; c < WORLD_COUNT; c++)
				{
					worldData_[c].world = buffer[count++];
					worldData_[c].in_progress = (bool)buffer[count++];
					worldData_[c].finished = (bool)buffer[count++];

					// for every level
					for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
							{
								worldData_[c].levelData[i].finished = buffer[count++];
								worldData_[c].levelData[i].star_num = buffer[count++];
								worldData_[c].levelData[i].animal.animal1 = (GAMEAPI_ANIMAL)buffer[count++]; 
								worldData_[c].levelData[i].animal.collected1 = (GAMEAPI_ANIMAL)buffer[count++];// deprecated
								worldData_[c].levelData[i].animal.animal2 = (GAMEAPI_ANIMAL)buffer[count++];// deprecated
								worldData_[c].levelData[i].animal.collected2 = (GAMEAPI_ANIMAL)buffer[count++];// deprecated


							}
				}

	// visualize
	//for (int c = 0; c < WORLD_COUNT; c++)
	//{
	//	for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
	//	{
	//		gLog->AppendLog("Worlddata[%d].leveldata[%d].finished = %d", c, i, worldData_[c].levelData[i].finished);
	//	}
	//}

	delete []buffer;
	current_world_ = GetLastFinishedWorld();
	currentLevel_ = GetLastFinishedLevel(current_world_);



	return 0;
}
//______________________________________________________________________________________________//


int I_cGameData::NextLevel(void)
{
	currentLevel_++;
    return currentLevel_;
}


void I_cGameData::ResetLevel(void)
{
	currentLevel_ = 0;
}

void I_cGameData::NextWorld(void)
{
 current_world_++;
 if (current_world_ > WORLD_CANDYLAND)
     ResetWorld();
}

void I_cGameData::ResetWorld(void)
{
 current_world_ = 0;
}



void I_cGameData::SetLevelFinished(int starcnt)
{
	gGameData.worldData_[current_world_].levelData[currentLevel_].finished = true;
	gGameData.worldData_[current_world_].levelData[currentLevel_].star_num = starcnt;
}




// some game states
void I_cGameData::SetAnimalCollected(int world, int level, int num)
{
	if (num == 1)
	{
		worldData_[world].levelData[level].animal.collected1 = true;
	}

	if (num == 2)
	{
		worldData_[world].levelData[level].animal.collected2 = true;
	}

}


// some game states
bool I_cGameData::IsAnimalCollected(int world, int level, int num)
{
 if (num == 1)
    {
	   return worldData_[world].levelData[level].animal.collected1;
		}

 if (num == 2)
    {
	   return worldData_[world].levelData[level].animal.collected2;
    }

 return true; 
}



// NOTE: can I do that here?
int I_cGameData::GetCurrentLevel(/*int world*/)
{ 
 return currentLevel_;
}



int I_cGameData::GetStarCount(int w, int l)
{
 return worldData_[w].levelData[l].star_num;
}


int I_cGameData::GetCurrentWorld()
{

	return current_world_;
}


// NOTE: Breaks when called gGameData.SetCurrentLevel but not dirrecty?
void I_cGameData::SetCurrentLevel(int l)
{
	currentLevel_ = l;
}


void I_cGameData::SetCurrentWorld(int w)
{
 current_world_ = w;
 currentLevel_ = GetLastFinishedLevel(w);
}


int I_cGameData::GetLastFinishedLevel(int world)
{
	 for (int c=0;c<GAMEAPI_LEVEL_COUNT;c++)
			 {
				if (worldData_[world].levelData[c].finished == false)
					 {
						return c;
					 }
		 }

	return 0;
}

int I_cGameData::GetLastFinishedWorld(void)
{
	for (int c = 0, count = 0; c < WORLD_COUNT; c++)
	{
	  printf("");
		if (worldData_[c].finished == false)
			return c;
	}

 return 0;
}




bool I_cGameData::IsWorldFinished(int world)
{
 return worldData_[world].finished;
}

bool I_cGameData::IsInProgress(int world)
{
	return worldData_[world].in_progress;
}


void I_cGameData::SetWorldFinished(int world)
{
 worldData_[world].finished = true;
 
}


void I_cGameData::SetInProgress(int world, bool p)
{
 worldData_[world].in_progress = p;
}


bool I_cGameData::IsLevelFinished(int world, int level)
{
 return worldData_[world].levelData[level].finished;
}



void I_cGameData::ResetCounters(void)
{
 printf("reseting counters\n");
 balloons_miss_ = 0;
 letter_miss_ = 0;
 balloons_pop_ = 0;
}


//  Phase1 finished. User has finished a game for the first time
void I_cGameData::ChangeGamePhase(void)
{
	int animal = 0;
	for (int c = 0, count = 0; c < WORLD_COUNT; c++)
	{
		worldData_[c].world = c;
		worldData_[c].in_progress = false;
		worldData_[c].finished = false;

		for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
		{
			worldData_[c].levelData[i].finished = false;
			worldData_[c].levelData[i].star_num = 255;
			worldData_[c].levelData[i].animal.animal1 = (GAMEAPI_ANIMAL)animal;
			worldData_[c].levelData[i].animal.collected1 = true;
			worldData_[c].levelData[i].animal.animal2 = (GAMEAPI_ANIMAL)animal;
			worldData_[c].levelData[i].animal.collected2 = false;
			animal++;
		}
	}

    SaveGameData();
    LoadGameData();

}

void I_cGameData::ResetGameData(void)
{
  int animal = 0;
	GAMEAPI_Phase_ = GAMEAPI_PHASE_1;
	for (int c = 0, count = 0; c < WORLD_COUNT; c++)
	{
		worldData_[c].world = c;
		worldData_[c].in_progress = false;
		worldData_[c].finished = false;

		for (int i = 0; i < GAMEAPI_LEVEL_COUNT; i++)
		{
			//worldData_[c].levelData[i].level = i;
			worldData_[c].levelData[i].finished = false;
			worldData_[c].levelData[i].star_num = 255;
			//worldData_[c].levelData[i].in_progress = false;
			worldData_[c].levelData[i].animal.animal1 = (GAMEAPI_ANIMAL)animal;
			worldData_[c].levelData[i].animal.collected1 = false;
			worldData_[c].levelData[i].animal.animal2 = (GAMEAPI_ANIMAL)animal;
			worldData_[c].levelData[i].animal.collected2 = false;
			animal++;
		}
	}

}

GAMEAPI_ANIMAL I_cGameData::GetLevelAnimal(int world, int level, int num)
{
	if (num == 1)
	{
		return worldData_[world].levelData[level].animal.animal1;
	}

	if (num == 2)
	{
		return worldData_[world].levelData[level].animal.animal2;
	}

	//SaveGameData();
}




void I_cGameData::UpdateBalloonsMissed(void)
{
 balloons_miss_++;
}

void I_cGameData::UpdateLettersMissed(void)
{
 letter_miss_++;
}


void I_cGameData::UpdateBalloonsPop(void)
{
	balloons_pop_++;
}


bool I_cGameData::IsGameOver(void)
{
     for (int c=0;c<WORLD_COUNT;c++)
         {
          for (int i=0;i<GAMEAPI_LEVEL_COUNT;i++)
		      {
		       if (gGameData.worldData_[c].finished == true)
			      {

			       if (gGameData.worldData_[c].levelData[i].star_num < 3)
                      {
				       return false;
                      }
			      }else {
                         return false;
                        }
		      }
	     }

     return true;
}



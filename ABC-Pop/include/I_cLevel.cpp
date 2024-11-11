#include "I_cLevel.h"
#include "I_cAssetmanager.h"
#include "anduin/anduin.h"
#include "include/I_cSoundBlaster.h"
#include "include/I_cGameData.h"

I_cLevel::I_cLevel()
{
}


I_cLevel::~I_cLevel()
{


}


void I_cLevel::Init(SDL_Texture *image, string str, GAMEAPI_WORLD_TYPE world, int level)
{

 textBar.Init(str, image, gAssetManager->GetTextbarPanel());
 lifeBar.Init();

 generateCollectable_ = true;
 collectable = NULL;

 
 SetParalax(world);


 left_rect = GAMEAPI_GetRect(-30,0,10,GAMEAPI_WINDOW_H);    // collision events
 right_rect = GAMEAPI_GetRect(GAMEAPI_WINDOW_W, 0, 10, GAMEAPI_WINDOW_H);
 
  // box2d collision body to use as an event to remove letters out of screen
 body_left_wall = GAMEAPI_AddRect_test(-30,0,10,GAMEAPI_WINDOW_H);
 body_right_wall = GAMEAPI_AddRect_test(GAMEAPI_WINDOW_W+30, 0, 10, GAMEAPI_WINDOW_H);
 update_ = true;
}


void I_cLevel::Reinit(void)
{
 textBar.Reinit();
}



void I_cLevel::Reset(void)
{
	std::list<I_cBalloon*>::iterator it;
	for (it = vBalloonList.begin(); it != vBalloonList.end(); it++)
	{
		I_cBalloon *ptr_balloon = *it;
		delete ptr_balloon;
		ptr_balloon = NULL;
	}



	for (size_t c = 0; c < vLetterList.size(); c++)
	{
		I_cLetter *ptr_letter = vLetterList[c];
		delete ptr_letter;
		ptr_letter = NULL;
	}

	std::list<I_cStarDroplet*>::iterator stars_it = vStarList.begin();
	for (stars_it = vStarList.begin(); stars_it != vStarList.end(); stars_it++)
	    {
         I_cStarDroplet *ptr_star = *stars_it;
		 delete ptr_star;
		 ptr_star = NULL;
        }

    vStarList.clear();
	vLetterList.clear();
	vBalloonList.clear();


	delete collectable;
	collectable = NULL;



	textBar.Reset();
	lifeBar.Reset();
}


// DEPRECATED: test static rect body
b2Body *I_cLevel::GAMEAPI_AddRect_test(int x, int y, int w, int h)
{


	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody; 
	bodyDef.position.Set(GAMEAPI_Pix2Meter(x + w / 2), GAMEAPI_Pix2Meter(y + h / 2)); //pos of the body in the box2d space
	b2Body *body = GAMEAPI_world_down->CreateBody(&bodyDef);


	b2PolygonShape staticBox;
	staticBox.SetAsBox(GAMEAPI_Pix2Meter(w)/2, GAMEAPI_Pix2Meter(h)/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;  

	body->CreateFixture(&fixtureDef);

	return body;
}


// DEPRECATED
void I_cLevel::test_draw_rect(b2Body *ptr_body)
{
	b2Vec2 center = ptr_body->GetPosition();


	SDL_Rect rect;
	rect.w = left_rect.w;
	rect.h = left_rect.h;

	float f1 = (center.x * GAMEAPI_M2P) - rect.w / 2;
	float f2 = (center.y * GAMEAPI_M2P) - rect.h / 2;
	float f3 = rect.w;
	float f4 = rect.h;
	SDL_Rect rct = { (int)f1 ,(int)f2,(int)f3,(int)f4 };


	SDL_RenderDrawRect(gAssetManager->GetRenderer(), &rct);
}





void I_cLevel::SetParalax(GAMEAPI_WORLD_TYPE type)
{
	paralax.Init(type);
}




void I_cLevel::OnClick(int mx, int my)
{

	
	std::list<I_cBalloon*>::iterator it;
	for (it = vBalloonList.begin(); it != vBalloonList.end(); it++) 
	    {
		 I_cBalloon *ptr_balloon = *it;
		 if (ptr_balloon->IsClicked(mx, my))
		 	{
			 gSoundBlaster.PlayPop();
			 ptr_balloon->Pop();

			 gGameData.UpdateBalloonsPop();

			 GAMEAPI_CallEvent(GAMEAPI_EVENT_CREATE_LETTER, ptr_balloon);
			}
	    }



 if (collectable && collectable->IsClicked(mx, my))
    {
	 SDL_Rect *rect = new SDL_Rect;
	 *rect = collectable->rect_;

	 gSoundBlaster.PlayPop();
	 GAMEAPI_CallEvent(GAMEAPI_EVENT_CREATE_JOKER, rect);

	 delete collectable;
	 collectable = NULL;
    }


}


void I_cLevel::OnClick_Letter(int mx, int my)
{

	for (size_t c = 0; c < vLetterList.size(); c++)
		{
		 I_cLetter *ptr_letter = vLetterList[c];
		 if (ptr_letter->IsClicked(mx, my))
	      	{
			 // ako slovo nije na traci, makni zvjezdicu i update missed letters
			 if (textBar.ContainsLetter(vLetterList[c]->GetLetter()) == false)
			    {
			     lifeBar.RemoveLife();
				 gGameData.UpdateLettersMissed();
				 gSoundBlaster.PlayLetterMiss();
			    }else {
					   textBar.Update(vLetterList[c]->GetLetter());
					   gSoundBlaster.PlayLetterHit();
                       CreateStars(mx, my);
					  }
							    
			 vLetterList.erase(vLetterList.begin() + c);
			 delete ptr_letter;
			}
        }
}


// This is where level is drawn per frame
void I_cLevel::Draw(bool update)
{
	// background
	paralax.Draw(4, update);
	paralax.Draw(3, update);
	paralax.Draw(2, update);
	paralax.Draw(1, update);


	// foreground
	std::list<I_cBalloon*>::iterator it = vBalloonList.begin();
	while (it != vBalloonList.end())
	      {
		   I_cBalloon *ptr_balloon = *it;
		   ptr_balloon->Draw();
		   it++;
		  }


	// hide ballon creation behind layer 0
	paralax.Draw(0, update);

	// joker
	if (collectable)
	   {
		collectable->Draw(update_);
		if (collectable->rect_.x <= -collectable->rect_.w)  // delete if oor
		   {
			delete collectable;
			collectable = NULL;
		   }
	   }

	// draw letter buffer
	for (int c = 0; c < vLetterList.size(); c++)
	    {
		 I_cLetter *ptr_letter = vLetterList[c];
		 ptr_letter->Draw();

		 if (ptr_letter->letter_rect_.y > GAMEAPI_WINDOW_H + 100)
		    {
			 // update player data
			 if (textBar.ContainsLetter(ptr_letter->GetLetter()))  
			    {
				 gGameData.UpdateLettersMissed();
				}

			 vLetterList.erase(vLetterList.begin() + c);
             delete ptr_letter;
             ptr_letter = NULL;
		    }
	    }


	it = vBalloonList.begin();
	while (it != vBalloonList.end())
	      {
		   I_cBalloon *ptr_balloon = *it;

		   // one of the 2 will always happen 
		   if (ptr_balloon->delete_ == true || ptr_balloon->balloon_rect_.y < -ptr_balloon->balloon_rect_.h)
			  {
			   gGameData.UpdateBalloonsMissed();

			   it = vBalloonList.erase(it);
			   delete ptr_balloon;
			   ptr_balloon = NULL;
			  }else it++;
		  }



	textBar.Draw();
	lifeBar.Draw();

	test_draw_rect(body_left_wall);
	test_draw_rect(body_right_wall);

    DrawStars();

}




// from engine
void I_cLevel::CreateBalloon(void)
{
	I_cBalloon *balloon = new I_cBalloon();
	int i = rm->IRandom(0, GAMEAPI_WINDOW_W);
	int small = rm->IRandom(0, 1);

    //  
	balloon->Init(i, GAMEAPI_WINDOW_H, small);
	vBalloonList.push_back(balloon);


	if (collectable == NULL)
	   {
			int col = rm->IRandom(0, 30);
			if (col == 0)
				 {
					CreateCollectableBalloon();
				 }
		 }
	   
      
}


int I_cLevel::GetStarCount(void)
{
 return  lifeBar.GetStarCount();
}


void I_cLevel::ResetStars(void)
{
 lifeBar.Reset();
}



void I_cLevel::CreateCollectableBalloon(void)
{
	collectable = new I_cCollectable();
	collectable->tex = gAssetManager->GetBalloon_Unknown();
}



string I_cLevel::GetRandomTextBarLetter(void)
{
 return textBar.GetRandomTextBarLetter();
}





int I_cLevel::Finish(void)
{
 return GetStarCount();
}



void I_cLevel::DrawStars(void)
{
    // crtaj balone
	std::list<I_cStarDroplet*>::iterator it = vStarList.begin();
	while (it != vStarList.end())
	      {
           I_cStarDroplet *ptr_star = *it;
		   ptr_star->Draw(); 


           if (ptr_star->star_rect_.y > GAMEAPI_WINDOW_H)
			  {
		       it = vStarList.erase(it);
			   delete ptr_star;
			   ptr_star = NULL;
              }else it++;
          }

}



void I_cLevel::CreateStars(int x, int y)
{

    int r = rm->IRandom(3, 7);
    for (int c=0;c<r;c++)
        {
         I_cStarDroplet *drop = new I_cStarDroplet();
         drop->Init(x,y,AndUIn::White);
         vStarList.push_back(drop);
        }
}
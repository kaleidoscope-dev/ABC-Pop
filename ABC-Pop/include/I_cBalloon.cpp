#include "I_cBalloon.h"
#include <time.h>
#include "I_cAssetmanager.h"
#include "letterdef.h"
#include "I_cGameData.h"

I_cBalloon::I_cBalloon()
{


}


I_cBalloon::~I_cBalloon()
{
	GAMEAPI_world_up->DestroyBody(world_body_);
}


void I_cBalloon::Init(float startx, float starty, GAMEAPI_BALLOON_COLOR type, bool small)
{

  small_ = small;

	balloon_rect_.x = startx;
	balloon_rect_.y = starty;
	if (small_)
	   {
	    balloon_rect_.w = GAMEAPI_BALLOON_W;
	    balloon_rect_.h = GAMEAPI_BALLOON_H;
		 }else {

						balloon_rect_.w = GAMEAPI_BALLOON_W /2;
						balloon_rect_.h = GAMEAPI_BALLOON_H /2;
					}


	delete_ = false;

	 SetType(type);


	 switch (balloon_type_)
	 {
	 case GAMEAPI_BALLOON_COLOR_BLUE:
	 //gAssetManager->getba
		 this->tex = gAssetManager->vTexBalloonBlue[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonBlue;
		 break;

	 case GAMEAPI_BALLOON_COLOR_GREEN:
		 this->tex = gAssetManager->vTexBalloonGreen[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonGreen;
		 break;

	 case GAMEAPI_BALLOON_COLOR_ORANGE:
		 this->tex = gAssetManager->vTexBalloonOrange[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonOrange;
		 break;

	 case GAMEAPI_BALLOON_COLOR_PINK:
		 this->tex = gAssetManager->vTexBalloonPink[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonPink;
		 break;

	 case GAMEAPI_BALLOON_COLOR_PURPLE:
		 this->tex = gAssetManager->vTexBalloonPurple[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonPurple;
		 break;

	 case GAMEAPI_BALLOON_COLOR_RED:
		 this->tex = gAssetManager->vTexBalloonRed[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonRed;
		 break;

	 case GAMEAPI_BALLOON_COLOR_YELLOW:
		 this->tex = gAssetManager->vTexBalloonYellow[0];
		 ptr_vTextureList = &gAssetManager->vTexBalloonYellow;
		 break;

	 default: break;
	 }
	

}


void I_cBalloon::Init(float startx, float starty, bool small)
{

 small_ = small;
 
 balloon_rect_.x = startx;
 balloon_rect_.y = starty;

 
 if (small_)
 {
	 balloon_rect_.w = GAMEAPI_BALLOON_W;
	 balloon_rect_.h = GAMEAPI_BALLOON_H;
 }
 else {

	 balloon_rect_.w = GAMEAPI_BALLOON_SMALL_W;
	 balloon_rect_.h = GAMEAPI_BALLOON_SMALL_H;
 }




 world_body_ = CreatePhysicBody(startx, starty);
 world_body_->SetGravityScale(2.0);

 pop_ = false;

 // SetType(GAMEAPI_BALLOON_COLOR_BLUE);
 int btype = rm->IRandom(1, 7);

 delete_ = false;

 balloon_type_ = (GAMEAPI_BALLOON_COLOR)btype;

// printf("type = %d\n", balloon_type_);
  SDL_Color clr = { 255,255,0 };
  int r = rm->IRandom(0,6);
  
  string s = letterIndexName[r].name;
  letter_.SetLetterProperties(s,startx,starty,20,20,clr);

 switch (balloon_type_)
 {
	case GAMEAPI_BALLOON_COLOR_BLUE:
	 this->tex = gAssetManager->vTexBalloonBlue[0];
	 ptr_vTextureList = &gAssetManager->vTexBalloonBlue;
	 break;

	case GAMEAPI_BALLOON_COLOR_GREEN:
		this->tex = gAssetManager->vTexBalloonGreen[0];
		ptr_vTextureList = &gAssetManager->vTexBalloonGreen;
		break;
	
	case GAMEAPI_BALLOON_COLOR_ORANGE:
		this->tex = gAssetManager->vTexBalloonOrange[0];
		ptr_vTextureList = &gAssetManager->vTexBalloonOrange;
		break;


	case GAMEAPI_BALLOON_COLOR_PINK:
		this->tex = gAssetManager->vTexBalloonPink[0];
		ptr_vTextureList = &gAssetManager->vTexBalloonPink;
		break;

	case GAMEAPI_BALLOON_COLOR_PURPLE:
		this->tex = gAssetManager->vTexBalloonPurple[0];
		ptr_vTextureList = &gAssetManager->vTexBalloonPurple;
		break;

	case GAMEAPI_BALLOON_COLOR_RED:
		this->tex = gAssetManager->vTexBalloonRed[0];
		ptr_vTextureList = &gAssetManager->vTexBalloonRed;
		break;

	case GAMEAPI_BALLOON_COLOR_YELLOW:
		this->tex = gAssetManager->vTexBalloonYellow[0];
		ptr_vTextureList = &gAssetManager->vTexBalloonYellow;
		break;
	default: break;
 }

 if (!tex)
      tex = gAssetManager->GetTODO();
    


}


void I_cBalloon::Pop(void)
{
 
 pop_ = true;
}


void I_cBalloon::Draw(int x, int y)
{
	SDL_Rect *rect = &balloon_rect_;
    rect->x = x;
    rect->y = y;

    SDL_RenderCopy(gAssetManager->GetRenderer(), tex, NULL, rect);

}


void I_cBalloon::Draw(void)
{

	b2Body *ptr_body = world_body_;
	b2Vec2 vel = ptr_body->GetLinearVelocity();

	b2Vec2 center = ptr_body->GetPosition();


	SDL_Rect *rect = &balloon_rect_;

	float f1 = (center.x * GAMEAPI_M2P) - rect->w / 2;
	float f2 = (center.y * GAMEAPI_M2P) - rect->h / 2;
	float f3 = rect->w;
	float f4 = rect->h;
	SDL_Rect rct = { (int)f1 ,(int)f2,(int)f3,(int)f4 };

	balloon_rect_.x = rct.x;
	balloon_rect_.y = rct.y;



	if (pop_)
		 {
		  int cur_frame = anima_.GetCurrentFrame();
			
			if (cur_frame == 5)
				  delete_ = true;  // pop sprite count is 5. It's safe to delete 


			anima_.OnAnimate();
			tex = ptr_vTextureList->at(anima_.GetCurrentFrame());
		 }

	    SDL_RenderCopy(gAssetManager->GetRenderer(), tex, NULL, &rct);

}



void I_cBalloon::DrawLetter(void)
{
 letter_.Draw();  
}




void I_cBalloon::Draw_rct(void)
{

 SDL_Color clr = {255,0,0};

 SDL_SetRenderDrawColor(gAssetManager->GetRenderer(), clr.r, 0, 0, 255);
 SDL_RenderDrawRect(gAssetManager->GetRenderer(), &balloon_rect_);
 SDL_SetRenderDrawColor(gAssetManager->GetRenderer(), 0, 0, 0, 255);
}





bool I_cBalloon::IsClicked(int mx, int my)
{
 SDL_Point pt;
 pt.x = mx;
 pt.y = my;

 if (SDL_PointInRect(&pt,&balloon_rect_))
     return true;


 return false;
}



GAMEAPI_BALLOON_COLOR I_cBalloon::GetType(void)
{
 return balloon_type_;
}

void I_cBalloon::SetType(GAMEAPI_BALLOON_COLOR type)
{
	balloon_type_ = type;
}



b2Body *I_cBalloon::CreatePhysicBody(float px, float py)
{
	// Create a body def and set it's position 
	b2BodyDef bodyDef;
	bodyDef.position.Set(GAMEAPI_Pix2Meter(px), GAMEAPI_Pix2Meter(py));

	// create the shape of our body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GAMEAPI_Pix2Meter(GAMEAPI_BALLOON_W) / 2, GAMEAPI_Pix2Meter(GAMEAPI_BALLOON_H) / 2);

	bodyDef.type = b2_dynamicBody; // gravity will infuence the body

	// Set the properties of our body
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;  // our shape
	fixtureDef.density = 1.0;
	//fixture_def.friction = 0.9;    // ice
	fixtureDef.restitution = 0.1;   // rubber

	// create a body in our physics syste
	b2Body *body = GAMEAPI_world_up->CreateBody(&bodyDef);


	// TODO: check
	fixtureDef.filter.categoryBits = GAMEAPI_COLLISION_BIT_CRITTER;  // is a:
	fixtureDef.filter.maskBits = GAMEAPI_COLLISION_BIT_SURFACE | GAMEAPI_COLLISION_BIT_SENSOR;  // Reacts to: (ie. if pu we put GAMEAPI_COLLISION_BIT_CRITTER it will react to itself)
	fixtureDef.filter.groupIndex = 0;

	// Set fixtue to a body
	body->CreateFixture(&fixtureDef);
	return  body;
}

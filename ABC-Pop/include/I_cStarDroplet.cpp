#include "I_cStarDroplet.h"
#include "gameapi.h"
#include "I_cAssetmanager.h"
#include "letterdef.h"

I_cStarDroplet::I_cStarDroplet()
{


}


I_cStarDroplet::~I_cStarDroplet()
{
 GAMEAPI_world_down->DestroyBody(world_body_);
}



void I_cStarDroplet::Init(float startx, float starty, SDL_Color clr)
{

	star_rect_.x = startx;
	star_rect_.y = starty;
	star_rect_.w = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W,5);
	star_rect_.h = GAMEAPI_GetPercentage(GAMEAPI_WINDOW_W,5);


	world_body_ = CreatePhysicBody(startx, starty);
	world_body_->SetGravityScale(2.0);

	b2Vec2 vel = world_body_->GetLinearVelocity();
	float f = (float)rm->IRandom(1, 10);
	vel.y = -f;   // brzina padanja 

	//vel.y = -10.0f;
	vel.x = (float)rm->IRandom(-7, 7);   // generiraj random smjer kretanja po x osi ljevo/desno
	world_body_->SetLinearVelocity(vel);


	posx_ = startx;
	posy_ = starty;



	tex = gAssetManager->GetStarGold();

}





bool I_cStarDroplet::Draw(void)
{

	b2Body *ptr_body = world_body_;
	b2Vec2 vel = ptr_body->GetLinearVelocity();



	b2Vec2 center = ptr_body->GetPosition();


	SDL_Rect *rect = &star_rect_;

	float f1 = (center.x * GAMEAPI_M2P) - rect->w / 2;
	float f2 = (center.y * GAMEAPI_M2P) - rect->h / 2;
	float f3 = rect->w;
	float f4 = rect->h;
	SDL_Rect rct = { (int)f1 ,(int)f2,(int)f3,(int)f4 };

	star_rect_.x = rct.x;
	star_rect_.y = rct.y;
	//printf("%f, %f, %f, %f\n",f1,f2,f3,f4); fflush(stdout);

	//SDL_RenderDrawRect(gAssetManager->GetRenderer(),&rct);
	//Draw_rct();

	SDL_RenderCopy(gAssetManager->GetRenderer(), tex, NULL, &rct);
	//Draw_rct();

	return true;
}





void I_cStarDroplet::Draw_rct(void)
{

	SDL_Color clr = { 255,0,0 };

	//SDL_Rect rct = {}
	SDL_SetRenderDrawColor(gAssetManager->GetRenderer(), clr.r, 0, 0, 255);
	SDL_RenderDrawRect(gAssetManager->GetRenderer(), &star_rect_);
	SDL_SetRenderDrawColor(gAssetManager->GetRenderer(), 0, 0, 0, 255);
}







b2Body *I_cStarDroplet::CreatePhysicBody(float px, float py)
{
	// stvori definiciju tijela i postavi tijelo u fizickom svijetu
	b2BodyDef bodyDef;
	bodyDef.position.Set(GAMEAPI_Pix2Meter(px), GAMEAPI_Pix2Meter(py));

	// critter je kvadratno dinamicko tijelo. Sva kvadratna tijela se stvaraju oko koordinate px i py koja je uvijek centar kada se zove setAsBox
	// SetAsBox prima centar. U nasem slucaju Ako je critt_w = 20, onda p1(-1-1), p2 (1,-1) ili prevedeno u pixel p1(-10,-10)...
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GAMEAPI_Pix2Meter(GAMEAPI_BALLOON_W - 45) / 2, GAMEAPI_Pix2Meter(GAMEAPI_BALLOON_H - 35) / 2);

	bodyDef.type = b2_dynamicBody; // critter je dinamicko tijelo na koji utjece gravitacija


	// svako dinamicko tijelo mora imati fixturu koja odredjuje kako se tijelo ponasa u svijetu
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;  // svaka fixtura mora imati oblik
	fixtureDef.density = 1.0;
	//fixture_def.friction = 0.9;    // led
	fixtureDef.restitution = 0.1;   // guma

	// sada stvorimo fizicko tijelo sa definicijama koje smo specificirali
	b2Body *body = GAMEAPI_world_down->CreateBody(&bodyDef);



	// TODO: provjeriti
	fixtureDef.filter.categoryBits = GAMEAPI_COLLISION_BIT_CRITTER;  // is a 
	//fixtureDef.filter.maskBits = GAMEAPI_COLLISION_BIT_SURFACE | GAMEAPI_COLLISION_BIT_SENSOR | GAMEAPI_COLLISION_BIT_CRITTER;  // sudara se sa... npr ako tu stavimo GAMEAPI_COLLISION_BIT_CRITTER, onda ce se sudarati sami sa sobom
	fixtureDef.filter.maskBits = GAMEAPI_COLLISION_BIT_SURFACE | GAMEAPI_COLLISION_BIT_SENSOR;  // sudara se sa... npr ako tu stavimo GAMEAPI_COLLISION_BIT_CRITTER, onda ce se sudarati sami sa sobom
	fixtureDef.filter.groupIndex = 0;


	// i stvorimo fixturu za to tijelo
	body->CreateFixture(&fixtureDef);
	return  body;
}
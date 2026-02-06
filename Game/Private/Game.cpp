//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"
#include "Game/Public/Actors/Ball.h"
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/SubSystems/PhysicsSystem.h"
#include "Game/Public/SubSystems/RenderSystem.h"
#include "Game/Public/SubSystems/TickSystem.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Super Amazing Handsome Smart Superb Nice Good Fine Beautiful Game Engine";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	, mUp( false )
	, mDown( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	mFontID = mEngine->LoadFont( "Resources/IndieFlower-Regular.ttf", 32 );

	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	float Radius = 25.0f;

	exColor Color1;
	Color1.mColor[0] = 255;
	Color1.mColor[1] = 50;
	Color1.mColor[2] = 150;
	Color1.mColor[3] = 255;

	exColor Color2;
	Color2.mColor[0] = 255;
	Color2.mColor[1] = 50;
	Color2.mColor[2] = 50;
	Color2.mColor[3] = 255;

	mBall_First = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 300.0f), Radius, Color1);

	mBall_Second = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 100.0f), Radius, Color2);

	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_Second->GetComponentOfType<PhysicsComponent>()) {
		BallPhysicsComp->SetVelocity(exVector2(0.0f, 0.5f));
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// exColor is a unsigned Char
void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// SDL_Event can handle all the types of inputs, windows
void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------


void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys ); // Updates nKeys to  an int

	//mUp = pState[SDL_SCANCODE_UP];
	mUp = pState[SDL_SCANCODE_W];
	mDown = pState[SDL_SCANCODE_DOWN];

	// Those keyboard inputs are already built in
	// They are just enums as int 
	// you can add up to 64
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Run is like void Update()
//  - Fires every frame
//  - Delta is returned which is the time between each frame
void MyGame::Run( float fDeltaT )
{
	/*
	* // SNOWMAN
	if ( mUp )
	{
		mTextPosition.y -= 40.0f * fDeltaT;
	}
	else if ( mDown )
	{
		mTextPosition.y += 40.0f * fDeltaT;
	}

	exVector2 p1, p2;
	exColor c;
	float r;

	c.mColor[0] = 119;
	c.mColor[1] = 132;
	c.mColor[2] = 105;
	c.mColor[3] = 255;

	p1.x = 175.0f;
	p1.y = 175.0f;

	r = 25.0f;

	mEngine->DrawCircle( p1, r, c, 0 );

	p1.x = 100.0f;
	p1.y = 100.0f;

	p2.x = 200.0f;
	p2.y = 200.0f;

	c.mColor[0] = 255;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	mEngine->DrawBox( p1, p2, c, 1 );

	p1.x = 400.0f;
	p1.y = 400.0f;

	p2.x = 500.0f;
	p2.y = 500.0f;

	mEngine->DrawLineBox( p1, p2, c, 1 );

	p1.x = 400.0f;
	p1.y = 400.0f;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	mEngine->DrawCircle( p1, r, c, 2 );

	mEngine->DrawText( mFontID, mTextPosition, "VFS", c, 0 );

	// Snowman - Body
	p1.x = 600.0f;
	p1.y = 250.0f;

	c.mColor[0] = 255;
	c.mColor[1] = 255;
	c.mColor[2] = 255;

	mEngine->DrawCircle(p1, r, c, 2);

	p1.y = 309.0f;

	r = 35;

	mEngine->DrawCircle(p1, r, c, 2);

	p1.y = 384.0f;

	r = 45;

	mEngine->DrawCircle(p1, r, c, 2);

	// Snowman Eyes

	
	p1.x = 620.0f;
	p1.y = 250.0f;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	r = 5;

	mEngine->DrawCircle(p1, r, c, 1);

	p1.x = 580.0f;
	p1.y = 250.0f;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	r = 5;

	mEngine->DrawCircle(p1, r, c, 1);

	// Snowman Nose

	p1.x = 600.0f;
	p1.y = 225.0f;

	c.mColor[0] = 252;
	c.mColor[1] = 90;
	c.mColor[2] = 3;


	mEngine->DrawText(mFontID, p1, ">", c, 0);

	// Snowman Smile

	p1.x = 595.0f;
	p1.y = 240.0f;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;


	mEngine->DrawText(mFontID, p1, "o", c, 0);

	// Snowman Arms

	// Start
	p1.x = 630.0f;
	p1.y = 300.0f;

	//End
	p2.x = 670;
	p2.y = 275;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;


	mEngine->DrawLine(p1, p2, c, 0);

	// Start
	p1.x = 570.0f;
	p1.y = 300.0f;

	//End
	p2.x = 520;
	p2.y = 275;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;


	mEngine->DrawLine(p1, p2, c, 0);

	// Draw box

	// Start
	p1.x = 600.0f;
	p1.y = 250;

	//End
	p2.x = 625;
	p2.y = 275;

	//mEngine->DrawBox(p1, p2, c, 0);
	*/

	exVector2 BallVelocity(0.0f, 0.0f);
	if (mUp) {
		BallVelocity.y = -2.5f;
	}
	if (mDown) {
		BallVelocity.y = 2.5f;
	}

	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_First->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsComp->SetVelocity(BallVelocity);
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
	TICK_ENGINE.TickUpdate(fDeltaT);
	// mBall->SetBallPosition(mTextPosition);
}


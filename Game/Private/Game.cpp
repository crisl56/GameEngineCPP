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
#include "Game/Public/Actors/Square.h"
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/SubSystems/PhysicsSystem.h"
#include "Game/Public/SubSystems/RenderSystem.h"
#include "Game/Public/SubSystems/TickSystem.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Super Amazing Handsome Smart Superb Nice Good Fine Beautiful Pong Game";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
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
	
	//-----------------------------------------------------------------
	// Score Renderer Creation
	//-----------------------------------------------------------------
	
	// TODO: Add here Score Render creation
	
	// EXAMPLE
	// Text
	// mFontID = mEngine->LoadFont( "Resources/IndieFlower-Regular.ttf", 32 );
	//
	// mTextPosition.x = 50.0f;
	// mTextPosition.y = 50.0f;
	
	//-----------------------------------------------------------------
	// Pong Walls (Top & Bottom)
	//-----------------------------------------------------------------
	
	// TODO: Add here pong walls creation
	
	// EXAMPLES
	// Square
	
	// exVector2 Point1;
	// exVector2 Point2;
	//
	// Point1.x = 500;
	// Point1.y = 500;
	//
	// Point2.x = 600;
	// Point2.y = 600;

	// mSquare = Actor::SpawnActorOfType<Square>(exVector2(300.0f, 300.0f), Point1, Point2, Color1);
	
	//-----------------------------------------------------------------
	// Goal Actors (Left & Right)
	//-----------------------------------------------------------------
	
	// TODO: Add here goal actors creation
	
	//-----------------------------------------------------------------
	// Paddles Creation
	//-----------------------------------------------------------------
	
	// TODO: Add here paddles creation

	const float PaddleSpeed = 10.0f;

	exColor PaddleColor;
	PaddleColor.mColor[0] = 115;
	PaddleColor.mColor[1] = 115;
	PaddleColor.mColor[2] = 115;
	PaddleColor.mColor[3] = 255;

	const float Paddle1Width = 40.0f;
	const float Paddle1Height = 80.0f;
	const exVector2 InitialPaddle1Position(10.0f, 250.0f);

	mPlayer1 = Actor::SpawnActorOfType<PlayerActor>(exVector2(InitialPaddle1Position.x, InitialPaddle1Position.y), PaddleSpeed ,PaddleColor, mPlayerOneUp, mPlayerOneDown, Paddle1Width, Paddle1Height);
	
	const exVector2 InitialPaddle2Position(790.0f, 250.0f);
	mPlayer2 = Actor::SpawnActorOfType<PlayerActor>(exVector2(InitialPaddle2Position.x, InitialPaddle2Position.y), PaddleSpeed ,PaddleColor, mPlayerOneUp, mPlayerOneDown, Paddle1Width, Paddle1Height);
	
	//-----------------------------------------------------------------
	// Pong Ball Creation
	//-----------------------------------------------------------------
	
	const float BallRadius = 25.0f;
	const exVector2 BallInitialPosition(100.0f, 250.0f);
	const exVector2 BallInitialVelocity(15.0f, 0.0f);
	
	exColor BallColor;
	BallColor.mColor[0] = 255;
	BallColor.mColor[1] = 50;
	BallColor.mColor[2] = 150;
	BallColor.mColor[3] = 255;

	mBall = Actor::SpawnActorOfType<Ball>(exVector2(BallInitialPosition.x, BallInitialPosition.y), BallRadius, BallColor);
	
	// Initialize ball with an initial velocity
	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall->GetComponentOfType<PhysicsComponent>()) 
	{
		BallPhysicsComp->SetVelocity(exVector2(BallInitialVelocity.x, BallInitialVelocity.y));
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

	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];

	// Using up arrow and down arrow
	//mPlayerOneUp = std::make_shared<bool>(pState[SDL_SCANCODE_UP]);
	//mPlayerOneDown = std::make_shared<bool>(pState[SDL_SCANCODE_DOWN]);

	//mPlayerOneUp = std::make_shared<bool>(pState[SDL_SCANCODE_UP]);
	//mPlayerOneDown = std::make_shared<bool>(pState[SDL_SCANCODE_DOWN]);

	// using w and s
	mPlayerTwoUp = pState[SDL_SCANCODE_W];
	mPlayerTwoDown = pState[SDL_SCANCODE_S];


	// Those keyboard inputs are already built in
	// They are just enums as int 
	// you can add up to 64
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Run is like void Update()
//  - Fires every frame
//  - Delta is returned which is the time between each frame
void MyGame::Run( float fDeltaT)
{
	exVector2 p1, p2;
	exColor c;

	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 255;
	c.mColor[3] = 255;

	// Start
	p1.x = 10;
	p1.y = 10;

	//End
	p2.x = 10;
	p2.y = 10;

	exVector2 PlayerOneVelocity(0.0f, 0.0f);
	if (mUp)
	{
		PlayerOneVelocity.y = -2.5f;
	}

	if (mDown) 
	{
		PlayerOneVelocity.y = 2.5f;
	}

	exVector2 PlayerTwoVelocity(0.0f, 0.0f);
	if (mPlayerTwoUp) 
	{
		PlayerTwoVelocity.y = -2.5f;
	}

	if (mPlayerTwoDown)
	{
		PlayerTwoVelocity.y = 2.5f;
	}

	if (std::shared_ptr<PhysicsComponent> PlayerOnePhysicsComp = mPlayer1->GetComponentOfType<PhysicsComponent>())
	{
		PlayerOnePhysicsComp->SetVelocity(PlayerOneVelocity);
	}

	if (std::shared_ptr<PhysicsComponent> PlayerTwoPhysicsComp = mPlayer2->GetComponentOfType<PhysicsComponent>())
	{
		PlayerTwoPhysicsComp->SetVelocity(PlayerTwoVelocity);
	}

	mEngine->DrawBox(p1, p2, c, 0);

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
	TICK_ENGINE.TickUpdate(fDeltaT);
}
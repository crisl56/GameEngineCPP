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
	
	 mTextPosition.x = 50.0f;
	 mTextPosition.y = 50.0f;

	mFontID = mEngine->LoadFont("Resources/PixelifySans-VariableFont_wght.ttf", 32);

	mScoreKeeper = Actor::SpawnActorOfType<ScoreKeeper>(mTextPosition, mFontID);
	
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

	const float PaddleSpeed = 7.0f;

	exColor PaddleColor;
	PaddleColor.mColor[0] = 115;
	PaddleColor.mColor[1] = 115;
	PaddleColor.mColor[2] = 115;
	PaddleColor.mColor[3] = 255;

	const float PaddleWidth = 20.0f;
	const float PaddleHeight = 90.0f;

	const exVector2 InitialPaddle1Position(100.0f, 250.0f);

	mPlayer1 = Actor::SpawnActorOfType<PlayerActor>(exVector2(InitialPaddle1Position.x, InitialPaddle1Position.y), PaddleSpeed ,PaddleColor, mPlayerOneUp, mPlayerOneDown, PaddleWidth, PaddleHeight);
	
	const exVector2 InitialPaddle2Position(700.0f, 250.0f);
	mPlayer2 = Actor::SpawnActorOfType<PlayerActor>(exVector2(InitialPaddle2Position.x, InitialPaddle2Position.y), PaddleSpeed ,PaddleColor, mPlayerTwoUp, mPlayerTwoDown, PaddleWidth, PaddleHeight);
	
	//-----------------------------------------------------------------
	// Pong Ball Creation
	//-----------------------------------------------------------------
	
	const float BallRadius = 25.0f;
	const exVector2 BallInitialPosition(500.0f, 250.0f);
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

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
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
	// Those keyboard inputs are already built in
	// They are just enums as int 
	// you can add up to 64

	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState(&nKeys); // Updates nKeys to  an int

	// Using up arrow and down arrow

	*mPlayerOneUp = pState[SDL_SCANCODE_W];
	*mPlayerOneDown = pState[SDL_SCANCODE_S];

	// using w and s
	*mPlayerTwoUp = pState[SDL_SCANCODE_UP];
	*mPlayerTwoDown = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Run is like void Update()
//  - Fires every frame
//  - Delta is returned which is the time between each frame
void MyGame::Run( float fDeltaT)
{
	// SCORE_SYSTEM.SetP1Score(SCORE_SYSTEM.GetP1Score() + 1);
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
	TICK_ENGINE.TickUpdate(fDeltaT);
}
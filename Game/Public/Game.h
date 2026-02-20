//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Utils.h"
#include "Actors/PlayerActor.h"

class Ball;
class Square;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

private:

	exEngineInterface*			mEngine;

	// int							mFontID;

	bool						mUp;
	bool						mDown;

	// TODO: Change these to unsigned ints later
	std::shared_ptr<bool> mPlayerOneUp;
	std::shared_ptr<bool> mPlayerOneDown;

	bool mPlayerTwoUp;
	bool mPlayerTwoDown;

	exVector2					mTextPosition;

	std::shared_ptr<PlayerActor> mPlayer1;
	std::shared_ptr<PlayerActor> mPlayer2;

	std::shared_ptr<Ball>		mBall;
	// std::shared_ptr<Square>		mSquare;
};

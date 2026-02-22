#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Managers/GameManager.h"
#include "Game/Public/Managers/ScoreManager.h"
#include "Game/Public/Actor.h"
#include "Game/Public/SubSystems/PhysicsSystem.h"
#include "Game/Public/SubSystems/ScoreSystem.h"

Ball::Ball(float BallRadius, exColor BallColor)
{
	mRadius = BallRadius;
	mColor = BallColor;
}

void Ball::BeginPlay()
{
	Actor::BeginPlay();

	AddComponentOfType<CircleRenderComponent>(mColor, mRadius);
	AddComponentOfType<CircleColliderComponent>(mRadius);

	// Register reset callback with GameManager so the ball is repositioned on round reset
	GameManager::ResetEventSignature resetDel = [this]()
	{
		// Reset flag first
		mHasScoredThisRound = false;

		// Reset position
		if (std::shared_ptr<TransformComponent> TransformComp = GetComponentOfType<TransformComponent>())
		{
			TransformComp->SetLocation({ kInitialX, kInitialY });
		}

		// Reset velocity
		if (std::shared_ptr<PhysicsComponent> PhysComp = GetComponentOfType<PhysicsComponent>())
		{
			// Give a small random flip to X so rounds vary a bit
			int sign = (std::rand() % 2) ? 1 : -1;
			PhysComp->SetVelocity({ kInitialVelX * sign, kInitialVelY });
		}
	};

	GameManager::GetInstance().ListenForReset(resetDel);

	// Note: Game.cpp also sets an initial velocity after spawn; the reset callback will be used
	// when rounds are reset (or at StartGame) to reposition the ball.
}

void Ball::Tick(const float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);

	// Only check scoring when we have a transform
	if (mHasScoredThisRound) return;

	std::shared_ptr<TransformComponent> TransformComp = GetComponentOfType<TransformComponent>();
	if (!TransformComp) return;

	exVector2 pos = TransformComp->GetLocation();

	// Left goal: ball passed left edge -> player 2 scores
	if (pos.x <= kLeftGoalX)
	{
		mHasScoredThisRound = true;
		ScoreManager::GetInstance().IncrementP2();
		// Let GameManager reset the round (will call our reset callback)
		GameManager::GetInstance().ResetRound();
		return;
	}

	// Right goal: ball passed right edge -> player 1 scores
	if (pos.x >= kRightGoalX)
	{
		mHasScoredThisRound = true;
		ScoreManager::GetInstance().IncrementP1();
		GameManager::GetInstance().ResetRound();
		return;
	}
}

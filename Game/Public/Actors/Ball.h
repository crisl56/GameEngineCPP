#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Ball : public Actor 
{
public:
	Ball(float BallRadius, exColor BallColor);

	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaSeconds) override;

private:
	float mRadius;
	exColor mColor;

	// Simple guard to avoid double-scoring while waiting for a reset
	bool mHasScoredThisRound = false;

	// initial reset values (simple constants for this project)
	static constexpr float kInitialX = 500.0f;
	static constexpr float kInitialY = 300.0f;
	static constexpr float kInitialVelX = 10.0f;
	static constexpr float kInitialVelY = 1.0f;

	// goal thresholds (simple constants)
	static constexpr float kLeftGoalX = 0.0f;
	static constexpr float kRightGoalX = 1000.0f;
};


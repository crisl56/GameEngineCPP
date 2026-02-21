#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/SubSystems/ScoreSystem.h"

class ScoreKeeper : public Actor
{
public:

	// fontId should come from engine->LoadFont(), pass it in from Game.cpp
	ScoreKeeper(int fontId);

	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaSeconds) override;

private:

	// Called by ScoreSystem whenever either score changes
	void OnScoreChanged(int p1Score, int p2Score);

	int mFontId;

	// Kept alive as a member so we can unregister it later if needed
	ScoreEventSignature mScoreDelegate;
};
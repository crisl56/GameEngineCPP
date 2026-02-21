#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class WallActor : public Actor
{

public:

	WallActor(exColor color, float width, float height);

	virtual void BeginPlay() override;

	virtual void Tick(const float DeltaSceonds) override;

private:

	float mWidth;
	float mHeight;

	exColor mColor;

};


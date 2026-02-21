#include "Game/Public/Actors/WallActor.h"
#include "Game/Public/Components/SquareRenderComponent.h"
#include "Game/Public/Components/SquareColliderComponent.h"

WallActor::WallActor(exColor color, float width, float height) : mWidth(width), mHeight(height), mColor(color)
{
}

void WallActor::BeginPlay()
{
	Actor::BeginPlay();

	// Add relevant components here
	AddComponentOfType<SquareRenderComponent>(mColor, mWidth, mHeight);
	AddComponentOfType<SquareColliderComponent>(mWidth, mHeight);
}

void WallActor::Tick(const float DeltaSceonds)
{
	Actor::Tick(DeltaSceonds);
}
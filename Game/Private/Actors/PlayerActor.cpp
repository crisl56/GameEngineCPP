#pragma once
#include "Game/Public/Actors/PlayerActor.h"
#include "Game/Public/Components/SquareRenderComponent.h"
#include <Game/Public/Components/CircleColliderComponent.h>

PlayerActor::PlayerActor(float speed, exColor color, std::shared_ptr<bool> upKey, std::shared_ptr<bool> downKey, float width, float height)
	:mSpeed(speed),
	 mUpKey(upKey),
	 mDownKey(downKey),
	 mWidth(width),
	 mHeight(height),
	 mColor(color)
{
}

void PlayerActor::BeginPlay()
{
	Actor::BeginPlay();

	// add components here
	AddComponentOfType<SquareRenderComponent>(mColor, mWidth, mHeight);
	AddComponentOfType<CircleColliderComponent>(10.0f);


}

void PlayerActor::Tick(const float DeltaSceonds)
{
	Actor::Tick(DeltaSceonds);

	// check for up and down key
}

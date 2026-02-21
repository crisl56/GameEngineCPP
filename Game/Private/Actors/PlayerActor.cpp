#pragma once
#include "Game/Public/Actors/PlayerActor.h"
#include "Game/Public/Components/SquareRenderComponent.h"
#include "Game/Public/Components/SquareColliderComponent.h"

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

	// Add relevant components here
	AddComponentOfType<SquareRenderComponent>(mColor, mWidth, mHeight);
	AddComponentOfType<SquareColliderComponent>(mWidth, mHeight);
}

void PlayerActor::Tick(const float DeltaSceonds)
{
	Actor::Tick(DeltaSceonds);

	exVector2 PlayerVelocity(0.0f, 0.0f);

	// Check for up and down key
	if (*mUpKey) 
	{
		PlayerVelocity.y = -mSpeed;

	}
	if (*mDownKey) 
	{
		PlayerVelocity.y = mSpeed;
	}

	if (std::shared_ptr<PhysicsComponent> PlayerPhysicsComp = GetComponentOfType<PhysicsComponent>()) 
	{
		PlayerPhysicsComp->SetVelocity(PlayerVelocity);
	}
}

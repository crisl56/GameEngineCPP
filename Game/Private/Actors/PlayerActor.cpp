#pragma once
#include "Game/Public/Actors/PlayerActor.h"
#include "Game/Public/Components/SquareRenderComponent.h"
#include "Game/Public/Components/SquareColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"

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

	// Simple screen bounds (constants)
	const float TOP_BOUND = 100.0f;
	const float BOTTOM_BOUND = 500.0f;

	// Try to clamp movement while preserving the physics
	if (std::shared_ptr<PhysicsComponent> PlayerPhysicsComp = GetComponentOfType<PhysicsComponent>()) 
	{
		if (std::shared_ptr<TransformComponent> TransformComp = GetComponentOfType<TransformComponent>())
		{
			exVector2 currentPos = TransformComp->GetLocation();
			exVector2 desiredPos = currentPos + PlayerVelocity;

			float halfH = mHeight * 0.5f;
			if (desiredPos.y - halfH < TOP_BOUND) desiredPos.y = TOP_BOUND + halfH;
			if (desiredPos.y + halfH > BOTTOM_BOUND) desiredPos.y = BOTTOM_BOUND - halfH;

			exVector2 finalVel = desiredPos - currentPos;
			PlayerPhysicsComp->SetVelocity(finalVel);
		}
		else
		{
			PlayerPhysicsComp->SetVelocity(PlayerVelocity);
		}
	}
}

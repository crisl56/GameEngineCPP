#pragma once
#include "Game/Public/Actors/PlayerActor.h"

PlayerActor::PlayerActor(float speed, std::shared_ptr<bool> upKey, std::shared_ptr<bool> downKey)
	:mSpeed(speed),
	 mUpKey(upKey),
	 mDownKey(downKey)
{
}

void PlayerActor::BeginPlay()
{
	Actor::BeginPlay();


}

void PlayerActor::Tick(const float DeltaSceonds)
{
	Actor::Tick(DeltaSceonds);

	// check for up and down key
}

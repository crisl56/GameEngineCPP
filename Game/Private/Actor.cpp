#include "Game/Public/Actor.h"
#include "Game/Public/Actors/Ball.h"
#include "Game/Public/SubSystems/TickSystem.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	TICK_ENGINE.AddActor(weak_from_this());
}

void Actor::EndPlay()
{
	// TODO
}

void Actor::Tick(const float DeltaSceonds)
{
	for (std::shared_ptr<Component> ComponetIt : mComponents)
	{
		ComponetIt->Tick(DeltaSceonds);
	}
	// TODO
}

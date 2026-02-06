#include "Game/Public/Actor.h"
#include "Game/Public/Actors/Ball.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	// TODO
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

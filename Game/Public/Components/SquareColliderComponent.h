#pragma once
#include "Game/Public/Components/PhysicsComponent.h"
#include "Engine/Public/EngineTypes.h"

class SquareColliderComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{
	friend class Actor;

public:

private:
	exVector2 mP1; // Bottom-left corner (or min point)
	exVector2 mP2; // Top-right corner (or max point)
};

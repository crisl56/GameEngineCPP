#pragma once
#include "Game/Public/Components/PhysicsComponent.h"
#include "Engine/Public/EngineTypes.h"

class SquareColliderComponent : public Component
{
	friend class Actor;

public:
	float GetWidth() const;
	float GetHeight() const;
private:
	exVector2 mP1; // Bottom-left corner (or min point)
	exVector2 mP2; // Top-right corner (or max point)
};

#include "Game/Public/Components/SquareColliderComponent.h"

float SquareColliderComponent::GetWidth() const
{
	return mP2.x - mP1.x;
}

float SquareColliderComponent::GetHeight() const
{
	return mP2.y - mP1.y;
}
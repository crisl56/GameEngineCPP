#pragma once
#include "Game/Public/Components/PhysicsComponent.h"
#include "Engine/Public/EngineTypes.h"

class SquareColliderComponent : public PhysicsComponent
{
public:

	SquareColliderComponent() = delete;

	SquareColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity = { 0.0f, 0.0f },
		bool isStatic = false, bool isGravityEnabled = false);

	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent) override;
	virtual void CollisionResolution() override;

	float GetWidth() const;
	float GetHeight() const;

private:
	float mWidth;
	float mHeight;
	exVector2 mCeneter;
};

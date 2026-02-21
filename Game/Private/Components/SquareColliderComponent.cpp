#include "Game/Public/Components/SquareColliderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"

float SquareColliderComponent::GetWidth() const
{
	return mWidth;
}

float SquareColliderComponent::GetHeight() const
{
	return mHeight;
}

SquareColliderComponent::SquareColliderComponent(std::weak_ptr<Actor> owner, 
												 float width, 
												 float height, 
												 exVector2 velocity, 
												 bool isStatic, 
												 bool isGravityEnabled) :
												 PhysicsComponent(owner, velocity, isStatic, isGravityEnabled),
												 mWidth(width),
												 mHeight(height)
{
}

bool SquareColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
	if (otherComponent.expired()) return false;

	// Collisions with circle collider components
	if (std::shared_ptr<CircleColliderComponent> OtherCircleColliderComponent = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent.lock())) {
		// Owner Center Pos
		exVector2 SelfCenterPos;

		// Other Circle Center Pos
		exVector2 OtherCenterPos;

		// Get Center Pos
		if (!mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
			{
				SelfCenterPos = TransformComp->GetLocation();
			}
		}

		// Get Other Circle Pos
		if (!otherComponent.lock()->GetOwner().expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = OtherCircleColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>()) {
				OtherCenterPos = TransformComp->GetLocation();
			}
		}

		float testX = OtherCenterPos.x;
		float testY = OtherCenterPos.y;

		float circleX = OtherCenterPos.x;
		float circleY = OtherCenterPos.y;

		float selfX = SelfCenterPos.x;
		float selfY = SelfCenterPos.y;

		// closest edges
		if (circleX < selfX - (mWidth / 2.0f)) { testX = selfX - (mWidth / 2.0f); }
		else if (circleY < selfY + (mWidth / 2.0f)) { testX = selfX + (mWidth / 2.0f); }

		if (circleY < selfY - (mHeight / 2.0f)) { testY = selfY - (mHeight / 2.0f); }
		else if (circleY > selfY + (mHeight / 2.0f)) { testY = selfY + (mHeight / 2.0f); }

		float distX = circleX - testX;
		float distY = circleY - testY;

		float distance = (distX * distX) + (distY * distY);
		float circleRadius = OtherCircleColliderComponent->GetRadius();

		// check distance between the circle border and rectangle edge
		return distance <= (circleRadius * circleRadius);
	}

	// Collisions with other squares
	if (std::shared_ptr<SquareColliderComponent> OtherSquareColliderComponent = std::dynamic_pointer_cast<SquareColliderComponent>(otherComponent.lock())) {
		// Owner Center Pos
		exVector2 SelfCenterPos;

		// Other Circle Center Pos
		exVector2 OtherCenterPos;

		// Get Center Pos
		if (!mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
			{
				SelfCenterPos = TransformComp->GetLocation();
			}
		}

		// Get Other Circle Pos
		if (!otherComponent.lock()->GetOwner().expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = OtherSquareColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>()) {
				OtherCenterPos = TransformComp->GetLocation();
			}
		}

		// Compare edges
		float r1x = SelfCenterPos.x;
		float r1y = SelfCenterPos.y;
		float r1w = mWidth / 2.0f;
		float r1h = mHeight / 2.0f;

		float r2x = OtherCenterPos.x;
		float r2y = OtherCenterPos.y;
		float r2w = OtherSquareColliderComponent->GetWidth() / 2.0f;
		float r2h = OtherSquareColliderComponent->GetHeight() / 2.0f;

		if (r1x + r1w >= r2x &&    
			r1x <= r2x + r2w &&    
			r1y + r1h >= r2y &&    
			r1y <= r2y + r2h) {    
			return true;
		}
		return false;
	}


	return PhysicsComponent::IsCollisionDetected(otherComponent);
}

void SquareColliderComponent::CollisionResolution()
{
	PhysicsComponent::CollisionResolution();
}

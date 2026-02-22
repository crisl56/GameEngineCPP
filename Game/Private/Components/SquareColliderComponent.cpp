#include "Game/Public/Components/SquareColliderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"
#include <algorithm>

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
		// Rectangle (self) center
		exVector2 RectCenter;
		// Circle center
		exVector2 CircleCenter;

		// Get rectangle center (self)
		if (!mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
			{
				RectCenter = TransformComp->GetLocation();
			}
		}

		// Get circle center
		if (!otherComponent.lock()->GetOwner().expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = OtherCircleColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>()) {
				CircleCenter = TransformComp->GetLocation();
			}
		}

		// Rectangle bounds (treat Transform location as center)
		float halfW = mWidth * 0.5f;
		float halfH = mHeight * 0.5f;
		float rectMinX = RectCenter.x - halfW;
		float rectMaxX = RectCenter.x + halfW;
		float rectMinY = RectCenter.y - halfH;
		float rectMaxY = RectCenter.y + halfH;

		// Clamp circle center to rectangle to find closest point
		auto clamp = [](float v, float lo, float hi) {
			if (v < lo) return lo;
			if (v > hi) return hi;
			return v;
		};

		float closestX = clamp(CircleCenter.x, rectMinX, rectMaxX);
		float closestY = clamp(CircleCenter.y, rectMinY, rectMaxY);

		// Squared distance from circle center to closest point on rectangle
		float distX = CircleCenter.x - closestX;
		float distY = CircleCenter.y - closestY;
		float distanceSq = (distX * distX) + (distY * distY);

		float circleRadius = OtherCircleColliderComponent->GetRadius();

		// Collision if squared distance <= squared radius
		return distanceSq <= (circleRadius * circleRadius);
	}

	// Collisions with other squares
	if (std::shared_ptr<SquareColliderComponent> OtherSquareColliderComponent = std::dynamic_pointer_cast<SquareColliderComponent>(otherComponent.lock())) {
		// Owner Center Pos
		exVector2 SelfCenterPos;
		exVector2 OtherCenterPos;

		// Get Center Pos (self)
		if (!mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
			{
				SelfCenterPos = TransformComp->GetLocation();
			}
		}

		// Get Other Center Pos
		if (!otherComponent.lock()->GetOwner().expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = OtherSquareColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>()) {
				OtherCenterPos = TransformComp->GetLocation();
			}
		}

		// Convert to min/max AABB using centers and half extents
		float r1MinX = SelfCenterPos.x - (mWidth * 0.5f);
		float r1MaxX = SelfCenterPos.x + (mWidth * 0.5f);
		float r1MinY = SelfCenterPos.y - (mHeight * 0.5f);
		float r1MaxY = SelfCenterPos.y + (mHeight * 0.5f);

		float r2MinX = OtherCenterPos.x - (OtherSquareColliderComponent->GetWidth() * 0.5f);
		float r2MaxX = OtherCenterPos.x + (OtherSquareColliderComponent->GetWidth() * 0.5f);
		float r2MinY = OtherCenterPos.y - (OtherSquareColliderComponent->GetHeight() * 0.5f);
		float r2MaxY = OtherCenterPos.y + (OtherSquareColliderComponent->GetHeight() * 0.5f);

		bool overlapX = (r1MinX <= r2MaxX) && (r1MaxX >= r2MinX);
		bool overlapY = (r1MinY <= r2MaxY) && (r1MaxY >= r2MinY);

		bool colliding = overlapX && overlapY;

		return colliding;
	}

	return PhysicsComponent::IsCollisionDetected(otherComponent);
}

void SquareColliderComponent::CollisionResolution()
{
}

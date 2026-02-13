#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/SquareColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"

CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner, float radius,
												 exVector2 velocity,
												 bool isStatic,
												 bool isGravityEnabled) :
												 PhysicsComponent(owner, velocity, isStatic, isGravityEnabled),
												 mRadius(radius)
{
	
}

bool CircleColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent) 
{
	if (!otherComponent.expired()) 
	{
		// Handle Collisions with Circle Collider Components
		if (std::shared_ptr<CircleColliderComponent> OtherCircleColliderComponent = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent.lock())) 
		{
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
			
			exVector2 Length = SelfCenterPos - OtherCenterPos; 
			float DistanceSquared = (Length.x * Length.x) + (Length.y * Length.y); // gets the distance between the circles
			float RadiusSum = mRadius + OtherCircleColliderComponent->GetRadius();

			// we square the radius sum because our distance is square so we can avoid square root
			return DistanceSquared < (RadiusSum * RadiusSum);
		}

		// Handle Collisions with Square Collider Components
		if (std::shared_ptr<SquareColliderComponent> OtherSquareColliderComponent = std::dynamic_pointer_cast<SquareColliderComponent>(otherComponent.lock()))
		{
			// Owner Center Pos
			exVector2 SelfCenterPos;
			
			// Get Center Pos
			if (!mOwner.expired()) 
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>()) 
				{
					SelfCenterPos = TransformComp->GetLocation();
				}
			}
			
			// Other Square Variables
			exVector2 OtherCenterPos;
			float OtherWidth = OtherSquareColliderComponent->GetWidth();
			float OtherHeight = OtherSquareColliderComponent->GetHeight();
			
			// Get Square Center Pos
			if (!otherComponent.lock()->GetOwner().expired()) 
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = OtherSquareColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>()) 
					{
					OtherCenterPos = TransformComp->GetLocation();
				}
			}
			
			// Calculate closest edges
			float testX = SelfCenterPos.x;
			float testY = SelfCenterPos.y;
			
			// Closest X edge
			if (SelfCenterPos.x < OtherCenterPos.x) testX = OtherCenterPos.x;
			else if (SelfCenterPos.x > OtherCenterPos.x + OtherWidth) testX = OtherCenterPos.x + OtherWidth;
			// Closest Y edge
			if (SelfCenterPos.y < OtherCenterPos.y) testY = OtherCenterPos.y;
			else if (SelfCenterPos.y > OtherCenterPos.y + OtherHeight) testY = OtherCenterPos.y + OtherHeight;
			
			// Get distance from closest edges
			float distX = SelfCenterPos.x - testX;
			float distY = SelfCenterPos.y - testY;
			float distance = sqrt(distX * distX + distY * distY);
			
			// Return true if distance is less or equals than radius
			return distance <= mRadius;
		} 
	}

	// parent function
	PhysicsComponent::IsCollisionDetected(otherComponent);
}

void CircleColliderComponent::CollisionResolution()
{
	exVector2 CurrentVelocty = GetVelocity();
	exVector2 ResolvedVelocity = CurrentVelocty * -1;

	SetVelocity(ResolvedVelocity);
}

float CircleColliderComponent::GetRadius() const
{
	return mRadius;
}

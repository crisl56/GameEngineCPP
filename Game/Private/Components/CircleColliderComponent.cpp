#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/SquareColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"
#include <cmath>
#include <cstdlib>

CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner, float radius, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
    PhysicsComponent(owner, velocity, isStatic, isGravityEnabled), mRadius(radius)
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
            // Circle center
            exVector2 SelfCenterPos;
            
            // Get Circle Center Pos
            if (!mOwner.expired()) 
            {
                if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>()) 
                {
                    SelfCenterPos = TransformComp->GetLocation();
                }
            }
            
            // Square center and extents
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
            
            // Treat OtherCenterPos as the rectangle center. Compute AABB bounds.
            float halfW = OtherWidth * 0.5f;
            float halfH = OtherHeight * 0.5f;
            float rectMinX = OtherCenterPos.x - halfW;
            float rectMaxX = OtherCenterPos.x + halfW;
            float rectMinY = OtherCenterPos.y - halfH;
            float rectMaxY = OtherCenterPos.y + halfH;

            // Clamp circle center to rectangle to find closest point
            auto clamp = [](float v, float lo, float hi) {
                if (v < lo) return lo;
                if (v > hi) return hi;
                return v;
            };

            float closestX = clamp(SelfCenterPos.x, rectMinX, rectMaxX);
            float closestY = clamp(SelfCenterPos.y, rectMinY, rectMaxY);

            // Get squared distance from circle center to closest point
            float distX = SelfCenterPos.x - closestX;
            float distY = SelfCenterPos.y - closestY;
            float distanceSq = (distX * distX) + (distY * distY);

            // Return true if squared distance is less or equals than squared radius
            return distanceSq <= (mRadius * mRadius);
        } 
    }

    // parent function
    return PhysicsComponent::IsCollisionDetected(otherComponent);
}

void CircleColliderComponent::CollisionResolution()
{   
    exVector2 CurrentVelocty = GetVelocity();

    // Inverse velocity then randomize direction (pong-like)
    exVector2 ResolvedVelocity = CurrentVelocty * -1.0f;

    // Change self color but clamp brightness so color is not too dark on black background
    if (!mOwner.expired())
    {
        exColor newColor;
        const int minBrightness = 120; // avoid too dark colors
        const int maxValue = 255;
        int range = (maxValue - minBrightness) + 1;
        newColor.mColor[0] = (std::rand() % range) + minBrightness; // R
        newColor.mColor[1] = (std::rand() % range) + minBrightness; // G
        newColor.mColor[2] = (std::rand() % range) + minBrightness; // B
        newColor.mColor[3] = 255; // fully opaque

        if (const std::shared_ptr<RenderComponent> RenderComp = mOwner.lock()->GetComponentOfType<RenderComponent>())
        {
            RenderComp->SetColor(newColor);
        }
    }

    SetVelocity(ResolvedVelocity);
}

float CircleColliderComponent::GetRadius() const
{
    return mRadius;
}

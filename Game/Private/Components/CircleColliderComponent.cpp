#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/SquareColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"
#include <cmath>
#include <cstdlib>

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
    // Get current velocity and invert it (basic reflection)
    exVector2 currentVelocity = GetVelocity();
    exVector2 inverted = currentVelocity * -1.0f;

    // Compute current speed (magnitude)
    float speed = std::sqrt((inverted.x * inverted.x) + (inverted.y * inverted.y));
    if (speed < 1e-4f) {
        // fallback speed if velocity was zero
        speed = 200.0f;
        inverted = exVector2{ speed, 0.0f };
    }

    // Base angle from inverted velocity
    const float PI = 3.14159265358979323846f;
    float baseAngle = std::atan2(inverted.y, inverted.x);

    // Add a small random angular jitter so bounces are not identical.
    // Keep it small for predictable gameplay but variable enough to feel dynamic.
    const float maxJitterDegrees = 20.0f; // small spread
    float jitterNorm = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f; // [-1,1]
    float jitterRadians = jitterNorm * (maxJitterDegrees * (PI / 180.0f));
    float finalAngle = baseAngle + jitterRadians;

    // Slight random speed variation so repeated bounces don't result in identical speeds
    const float maxSpeedVariation = 0.12f; // +/-12%
    float speedVarNorm = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
    float speedMultiplier = 1.0f + (speedVarNorm * maxSpeedVariation);

    exVector2 newVelocity;
    newVelocity.x = std::cos(finalAngle) * speed * speedMultiplier;
    newVelocity.y = std::sin(finalAngle) * speed * speedMultiplier;

    // Clamp a reasonable maximum speed to avoid runaway
    const float maxSpeed = 1200.0f;
    float newSpeed = std::sqrt(newVelocity.x * newVelocity.x + newVelocity.y * newVelocity.y);
    if (newSpeed > maxSpeed) {
        float scale = maxSpeed / newSpeed;
        newVelocity.x *= scale;
        newVelocity.y *= scale;
    }

    // Color change: avoid too dark colors on black background (keep it visible)
    if (!mOwner.expired())
    {
        exColor newColor;
        const int minBrightness = 130; // avoid too dark colors
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

    SetVelocity(newVelocity);
}

float CircleColliderComponent::GetRadius() const
{
    return mRadius;
}

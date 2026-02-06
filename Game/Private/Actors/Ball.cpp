#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"

Ball::Ball(float BallRadius, exColor BallColor)
{
	mRadius = BallRadius;
	mColor = BallColor;
}

//void Ball::Render(exEngineInterface* EngineInterface)
//{
//	if (EngineInterface) 
//	{
//		// Allows us to find component of type
//		if (std::shared_ptr<TransformComponent> TransformComp = GetComponentOfType<TransformComponent>())
//		{
//			EngineInterface->DrawCircle(TransformComp->GetLocation(), mRadius, mColor, 2);
//		}
//	}
//}

void Ball::BeginPlay()
{
	AddComponentOfType<TransformComponent>(exVector2{ 200.0f, 300.0f });
	AddComponentOfType<CircleRenderComponent>(exColor({ 0 , 255, 255, 255 }), 100.0f);
	AddComponentOfType<PhysicsComponent>();
}

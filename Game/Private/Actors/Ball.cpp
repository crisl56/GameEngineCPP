#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Utils.h"

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
	Actor::BeginPlay();

	AddComponentOfType<CircleRenderComponent>(mColor, mRadius);
	std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> ResultCircleCollider = AddComponentOfType<CircleColliderComponent>(mRadius);
	//AddComponentOfType<CircleColliderComponent>(mRadius+5.0f); // example 

	if(std::shared_ptr<CircleColliderComponent> CircleColliderComp = std::get<0>(ResultCircleCollider))
	{
		// NOTE: Both works
		//std::function<void(std::weak_ptr<Actor>, const exVector2)> CollisionDelgate = std::bind(&Ball::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		CollisionEventSignature CollisionDelgate = std::bind(&Ball::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		CircleColliderComp->ListenForCollision(CollisionDelgate);
	}
}

void Ball::OnCollision(std::weak_ptr<Actor>, const exVector2)
{
	if (std::shared_ptr<RenderComponent> RenderComp = GetComponentOfType<RenderComponent>()) {

		exColor Color1;
		Color1.mColor[0] = 20;
		Color1.mColor[1] = 255;
		Color1.mColor[2] = 120;
		Color1.mColor[3] = 255;

		RenderComp->SetColor(Color1);
	}
}

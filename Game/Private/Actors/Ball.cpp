#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Utils.h"

Ball::Ball(float BallRadius, exColor BallColor)
{
	mRadius = BallRadius;
	mColor = BallColor;
}

void Ball::BeginPlay()
{
	Actor::BeginPlay();

	AddComponentOfType<CircleRenderComponent>(mColor, mRadius);
	AddComponentOfType<CircleColliderComponent>(mRadius);

	// how transform????
	
	// std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> ResultCircleCollider = AddComponentOfType<CircleColliderComponent>(mRadius);
	//
	// if(std::shared_ptr<CircleColliderComponent> CircleColliderComp = std::get<0>(ResultCircleCollider))
	// {
	// 	CollisionEventSignature CollisionDelgate = std::bind(&Ball::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
	// 	CircleColliderComp->ListenForCollision(CollisionDelgate);
	// }
}



// void Ball::OnCollision(std::weak_ptr<Actor>, const exVector2)
// {
// 	if (std::shared_ptr<RenderComponent> RenderComp = GetComponentOfType<RenderComponent>()) {
//
// 		exColor Color1;
// 		Color1.mColor[0] = 20;
// 		Color1.mColor[1] = 255;
// 		Color1.mColor[2] = 120;
// 		Color1.mColor[3] = 255;
//
// 		RenderComp->SetColor(Color1);
// 	}
// }

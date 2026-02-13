#include "Game/Public/Actors/Square.h"
#include "Game/Public/Components/SquareRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Actor.h"

Square::Square(exVector2 p1, exVector2 p2, exColor SquareColor)
{
	mPoint1 = p1;
	mPoint2 = p2;
	mColor = SquareColor;
}

void Square::BeginPlay()
{
	Actor::BeginPlay();

	AddComponentOfType<SquareRenderComponent>(mColor, mPoint1, mPoint2);
}

void Square::OnCollision(std::weak_ptr<Actor>, const exVector2)
{
	// TODO: Create collision
}

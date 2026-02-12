#include "Game/Public/Actors/Square.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/SquareRenderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Utils.h"

Square::Square(float SquareSize, exColor SquareColor)
{
	mSize = SquareSize;
	mColor = SquareColor;
}

void Square::BeginPlay()
{
	Actor::BeginPlay();

	// Create a square with the given size
	// Bottom-left corner and top-right corner
	exVector2 bottomLeft(-mSize / 2.0f, -mSize / 2.0f);
	exVector2 topRight(mSize / 2.0f, mSize / 2.0f);

	AddComponentOfType<SquareRenderComponent>(mColor, bottomLeft, topRight);

}

void Square::OnCollision(std::weak_ptr<Actor>, const exVector2)
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
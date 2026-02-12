#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Square : public Actor
{
public:
	Square(float SquareSize, exColor SquareColor);

	virtual void BeginPlay() override;

	void OnCollision(std::weak_ptr<Actor>, const exVector2);

private:
	float mSize;
	exColor mColor;

};

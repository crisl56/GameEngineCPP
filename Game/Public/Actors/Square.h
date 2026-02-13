#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Square : public Actor
{
public:
	Square(exVector2 p1, exVector2 p2, exColor SquareColor);

	virtual void BeginPlay() override;

	void OnCollision(std::weak_ptr<Actor>, const exVector2);

private:
	exVector2 mPoint1;
	exVector2 mPoint2;
	exColor mColor;

};


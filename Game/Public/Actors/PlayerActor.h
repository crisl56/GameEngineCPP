#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class PlayerActor : public Actor 
{

public:
	PlayerActor(float speed, exColor color, std::shared_ptr<bool> upKey, std::shared_ptr<bool> downKey, float width, float height);

	virtual void BeginPlay() override;

	void OnCollision(std::weak_ptr<Actor>, const exVector2);

	virtual void Tick(const float DeltaSceonds) override;

private :
	float mSpeed;
	float mWidth;
	float mHeight;

	exColor mColor;

	std::shared_ptr<bool> mUpKey;
	std::shared_ptr<bool> mDownKey;
};
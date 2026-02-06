#pragma once
#include "Game/Public/Components/RenderComponent.h"
#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

class CircleRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	CircleRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

protected:

	CircleRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float Radius);

private:

	float mRadius;
};

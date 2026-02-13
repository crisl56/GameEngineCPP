#pragma once
#include "Game/Public/Components/RenderComponent.h"
#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

class SquareRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	SquareRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

protected:

	SquareRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, exVector2 p1, exVector2 p2);

private:

	exVector2 mP1;
	exVector2 mP2;

};

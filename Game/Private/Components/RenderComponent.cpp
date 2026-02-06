#include "Game/Public/Components/RenderComponent.h"
#include "Game/Public/SubSystems/RenderSystem.h"
#include "Game/Public/Utils.h"


void RenderComponent::Render(exEngineInterface* EngineInterface)
{
}

void RenderComponent::BeginPlay()
{
	Component::BeginPlay();

	RENDER_ENGINE.AddRenderComponent(weak_from_this());
}

void RenderComponent::SetColor(exColor newColor)
{
	mRenderColor = newColor;
}

RenderComponent::RenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor) :
	Component(owner), mRenderColor(RenderColor)
{

}

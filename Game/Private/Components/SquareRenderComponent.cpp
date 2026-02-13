#include "Game/Public/Components/SquareRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

void SquareRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		if (!mOwner.expired())
		{
			if (std::shared_ptr<Actor> owner = mOwner.lock())
			{
				if (std::shared_ptr<TransformComponent> TransformComp = owner->GetComponentOfType<TransformComponent>())
				{
					EngineInterface->DrawBox(mP1, mP2, mRenderColor, 1);
				}
			}
		}
	}
}

SquareRenderComponent::SquareRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, exVector2 p1, exVector2 p2) :
	RenderComponent(owner, RenderColor), mP1(p1), mP2(p2)
{

}

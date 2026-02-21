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
					exVector2 halfExtents = { mWidth / 2.f, mHeight / 2.f };

					exVector2 Center = TransformComp->GetLocation();

					exVector2 p1 = { Center.x - halfExtents.x, Center.y - halfExtents.y };
					exVector2 p2 = { Center.x + halfExtents.x, Center.y + halfExtents.y };
					EngineInterface->DrawBox(p1, p2, mRenderColor, 1);

					
				}
			}
		}
	}
}
SquareRenderComponent::SquareRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float width, float height) :
	RenderComponent(owner, RenderColor), mWidth(width), mHeight(height)
{
}
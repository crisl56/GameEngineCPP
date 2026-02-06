#include "Game/Public/SubSystems/RenderSystem.h"
#include "Game/Public/Components/RenderComponent.h"

std::unique_ptr <RenderEngine> RenderEngine::sRenderEngine = nullptr;


void RenderEngine::AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd)
{
	mRenderComponents.emplace_back(componentToAdd);
}

void RenderEngine::ClearInvalidRenderComponents()
{
	if (mRenderComponents.empty())
	{
		return;
	}

	mRenderComponents.remove_if(
		[](const std::weak_ptr<RenderComponent>& component) {
			return component.expired();
		});
}

void RenderEngine::RenderUpdate(exEngineInterface* EngineInterface)
{
	ClearInvalidRenderComponents();
	for (size_t index1 = 0; index1 < mRenderComponents.size(); ++index1) {
		auto RenderComponentIt = mRenderComponents.begin();
		std::advance(RenderComponentIt, index1);

		if (!RenderComponentIt->expired()) {
			std::shared_ptr<RenderComponent> RenderComponentToCheck = RenderComponentIt->lock();

			RenderComponentToCheck->Render(EngineInterface);
		}
	}
}

RenderEngine::RenderEngine()
{
}




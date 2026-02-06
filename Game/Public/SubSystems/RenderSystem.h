#pragma once
#include "Game/Public/Utils.h"
#include "Engine/Public/EngineInterface.h"


class RenderComponent;

#define RENDER_ENGINE RenderEngine::GetInstance()

class RenderEngine
{
public:
	static RenderEngine& GetInstance()
	{
		if (!sRenderEngine)
		{
			sRenderEngine.reset(new RenderEngine());
		}
		return *sRenderEngine;
	}

	void AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd);
	void ClearInvalidRenderComponents();

	void RenderUpdate(exEngineInterface* EngineInterface);
private:

	RenderEngine();

	// Delete the copy constructor and copy assignment so the singleton can't be copied over
	RenderEngine(const RenderEngine& OtherRender) = delete;
	RenderEngine& operator = (const RenderEngine& OtherRender) = delete;

	//Make sure you can only have one with unique_ptr
	static std::unique_ptr<RenderEngine> sRenderEngine;

	std::list<std::weak_ptr<RenderComponent>> mRenderComponents;
};
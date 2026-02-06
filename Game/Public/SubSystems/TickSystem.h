#pragma once
#include "Game/Public/Utils.h"
#include "Engine/Public/EngineInterface.h"

class Actor;

#define TICK_ENGINE TickEngine::GetInstance()

class TickEngine
{
public:
	static TickEngine& GetInstance()
	{
		if (!sTickEngine)
		{
			sTickEngine.reset(new TickEngine());
		}
		return *sTickEngine;
	}

	void AddActor(std::weak_ptr<Actor> actorToAdd);
	void ClearInvalidActors();

	void TickUpdate(const float DeltaTime);
private:

	TickEngine();

	// Delete the copy constructor and copy assignment so the singleton can't be copied over
	TickEngine(const TickEngine& OtherTickEngine) = delete;
	TickEngine& operator = (const TickEngine& OtherTickEngine) = delete;

	//Make sure you can only have one with unique_ptr
	static std::unique_ptr<TickEngine> sTickEngine;

	std::list<std::weak_ptr<Actor>> mActors;
};
#pragma once
#include "Game/Public/Utils.h"

class PhysicsComponent;

#define PHYSICS_ENGINE PhysicsEngine::GetInstance()

class PhysicsEngine
{
public:
	static PhysicsEngine& GetInstance()
	{
		if (!sPhysicsEngine)
		{
			sPhysicsEngine.reset(new PhysicsEngine());
		}
		return *sPhysicsEngine;
	}

	void AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd);
	void ClearInvalidPhysicsComponents();

	void PhysicsUpdate(const float DeltaTime);
private:

	PhysicsEngine();

	PhysicsEngine(const PhysicsEngine& OtherEngine) = delete;
	PhysicsEngine& operator = (const PhysicsEngine& OtherEngine) = delete;

	//Make sure you can only have one
	static std::unique_ptr<PhysicsEngine> sPhysicsEngine;

	std::list<std::weak_ptr<PhysicsComponent>> mPhysicsComponent;
};
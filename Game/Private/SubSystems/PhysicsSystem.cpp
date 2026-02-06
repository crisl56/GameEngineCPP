#include "Game/Public/SubSystems/PhysicsSystem.h"
#include "Game/Public/Components/PhysicsComponent.h"

std::unique_ptr <PhysicsEngine> PhysicsEngine::sPhysicsEngine = nullptr;

void PhysicsEngine::AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd)
{
	mPhysicsComponent.emplace_back(componentToAdd);
}

void PhysicsEngine::ClearInvalidPhysicsComponents()
{
	if (mPhysicsComponent.empty())
	{
		return;
	}

	mPhysicsComponent.remove_if(
		[](const std::weak_ptr<PhysicsComponent>& component) {
			return component.expired();
		});
}

void PhysicsEngine::PhysicsUpdate(const float DeltaTime)
{
	ClearInvalidPhysicsComponents();

	for (size_t index1 = 0; index1 < mPhysicsComponent.size(); ++index1)
	{
		auto firstPhysicsComponentIt = mPhysicsComponent.begin();
		std::advance(firstPhysicsComponentIt, index1);

		if (!firstPhysicsComponentIt->expired())
		{
			std::shared_ptr<PhysicsComponent> firstPhysicsComponentToCheck = firstPhysicsComponentIt->lock();

			for (size_t index2 = index1 + 1; index2 < mPhysicsComponent.size(); ++index1)
			{
				std::list<std::weak_ptr<PhysicsComponent>>::iterator secondPhysicsComponentIt = mPhysicsComponent.begin();
				std::advance(firstPhysicsComponentIt, index2);

				if (!secondPhysicsComponentIt->expired())
				{
					std::shared_ptr<PhysicsComponent> secondPhysicsComponentToCheck = secondPhysicsComponentIt->lock();

					if (firstPhysicsComponentToCheck->IsCollisionDetected(*secondPhysicsComponentIt))
					{
						// TODO add actual hitPosition
						firstPhysicsComponentToCheck->BroadcastCollisionEvents(secondPhysicsComponentToCheck->GetOwner(), { 0.0f, 0.0f });
						secondPhysicsComponentToCheck->BroadcastCollisionEvents(firstPhysicsComponentToCheck->GetOwner(), { 0.0f, 0.0f });

						firstPhysicsComponentToCheck->CollisonResolution();
						secondPhysicsComponentToCheck->CollisonResolution();
					}
				}
			}

			firstPhysicsComponentToCheck->DoPhysics();
		}
	}
}

PhysicsEngine::PhysicsEngine()
{
}

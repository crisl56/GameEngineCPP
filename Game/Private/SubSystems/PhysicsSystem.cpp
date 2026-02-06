#include "Game/Public/SubSystems/PhysicsSystem.h"
#include "Game/Public/Components/PhysicsComponent.h"

std::unique_ptr <PhysicsEngine> PhysicsEngine::sPhysicsEngine = nullptr;

// NOTE: we are using weak_ptr because the system is only responsible for handling physics and not storing them.
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
    for (size_t index1 = 0; index1 < mPhysicsComponent.size(); ++index1) {
        auto firstPhysicsComponentIt = mPhysicsComponent.begin();
        std::advance(firstPhysicsComponentIt, index1);

        if (!firstPhysicsComponentIt->expired())
        {
            std::shared_ptr<PhysicsComponent> firstPhysicsComponentToCheck = firstPhysicsComponentIt->lock();
            for (size_t index2 = index1 + 1; index2 < mPhysicsComponent.size(); ++index2)
            {
                auto secondPhysicsComponentIt = mPhysicsComponent.begin();
                std::advance(secondPhysicsComponentIt, index2);

                if (!secondPhysicsComponentIt->expired()) {
                    std::shared_ptr<PhysicsComponent> secondPhysicsComponenttoCheck = secondPhysicsComponentIt->lock();
                    if (firstPhysicsComponentToCheck->IsCollisionDetected(*secondPhysicsComponentIt)) {

                        firstPhysicsComponentToCheck->BroadcastCollisionEvents(secondPhysicsComponenttoCheck->GetOwner(), { 0.0f,0.0f });
                        secondPhysicsComponenttoCheck->BroadcastCollisionEvents(firstPhysicsComponentToCheck->GetOwner(), { 0.0f,0.0f });

                        firstPhysicsComponentToCheck->CollisionResolution();
                        secondPhysicsComponenttoCheck->CollisionResolution();

                        //secondPhysicsComponenttoCheck->DoPhysics();
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

#include "TickSystem.h"
#include "Game/Public/Actor.h"

std::unique_ptr <TickEngine> TickEngine::sTickEngine = nullptr;

void TickEngine::AddActor(std::weak_ptr<Actor> actorToAdd)
{
	mActors.emplace_back(actorToAdd);
}

void TickEngine::ClearInvalidActors()
{
	if (mActors.empty())
	{
		return;
	}

	mActors.remove_if(
		[](const std::weak_ptr<Actor>& actor) {
			return actor.expired();
		});
}

void TickEngine::TickUpdate(const float DeltaTime)
{
	ClearInvalidActors();
	for (size_t index1 = 0; index1 < mActors.size(); ++index1) {
		auto ActorIt = mActors.begin();
		std::advance(ActorIt, index1);

		if (!ActorIt->expired()) {
			std::shared_ptr<Actor> ActorToCheck = ActorIt->lock();

			ActorToCheck->Tick(DeltaTime);
		}
	}
}

TickEngine::TickEngine()
{
}

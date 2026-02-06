#pragma once
#include "Game/Public/Component.h"
#include <type_traits>
#include "Engine/Public/EngineTypes.h"

using CollisionEventSignature = std::function<void(std::weak_ptr<Actor>, const exVector2)>;

class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{
public:
	PhysicsComponent() = delete;

	// Not all actors need to move some just detect so add isStatic
	PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity = { 0.0f, 0.0f },
		bool isStatic = false, bool isGravityEnabled = false);

	virtual void BeginPlay() override;
	virtual void Tick(const float DeltalTime) override;

	//Can also do in tick
	virtual void DoPhysics();

#pragma region Collision

	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent);
	virtual void CollisonResolution();

	void ListenForCollision(CollisionEventSignature& delegateToAdd);
	void StopListeningForCollison(CollisionEventSignature& DelegateToRemove);
	void BroadcastCollisionEvents(std::weak_ptr<Actor> otherActor, const exVector2 hitLocation);

	exVector2 GetVelocity() const;
	void SetVelocity(exVector2 inVelocity);

private:

	// Bit field (Only used 1 bit of the 8 that comes in a bit)
	unsigned int mIsStatic : 1;
	unsigned int mIsGravityEnabled : 1;
	exVector2 mVelocity;

	// Saves all collison events 
	std::list<CollisionEventSignature> mCollisionEvents;

#pragma endregion
};
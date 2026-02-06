#pragma once

// Interface must have no function implemented

class ILifetimeInterface {
public:
	virtual void BeginPlay() = 0;
	virtual void EndPlay() = 0;
	virtual void Tick(const float DeltaTime) = 0;
};

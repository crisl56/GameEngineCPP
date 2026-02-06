#pragma once
#include <type_traits>
#include <memory>
#include "Game/Public/LifetimeInterface.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/ComponentTypes.h"

class Actor : public ILifetimeInterface, public std::enable_shared_from_this<Actor> // allows us to create shared pointer from self
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void Tick(const float DeltaSceonds) override;

private:

	// Stores all the components
	ComponentList mComponents;

#pragma region TemplateRegion

public:

	// typename ...Args means I can take multiple arbitrary amount of arguments
	template<std::derived_from<Component> ComponentType, typename ...Args>

	// bool is succuess for adding, string is debug message
	std::tuple<std::shared_ptr<ComponentType>, bool, String> AddComponentOfType(Args... Arguments)
	{
		// First method
		ComponentType* NewComponentPtr = new ComponentType(weak_from_this(), Arguments...);
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(*NewComponentPtr);
		delete NewComponentPtr;

		// Second method
		/*std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(weak_from_this());*/

		if (NewComponent->CanAddComponent())
		{
			NewComponent->BeginPlay();
			mComponents.emplace_back(NewComponent);
			return { NewComponent, true, "Component was created successfuly" };
		}

		return { nullptr, false, "Failed to add component" };
	}

	template<std::derived_from<Component> ComponentType>
	std::shared_ptr<ComponentType> GetComponentOfType()
	{
		for (std::shared_ptr<Component> ComponentItereator : mComponents)
		{
			if (std::shared_ptr<ComponentType> FoundComponent = std::dynamic_pointer_cast<ComponentType>(ComponentItereator))
			{
				return FoundComponent;
			}
		}

		return nullptr;
	}

	// TODO: write a function to return all the components of one type



#pragma endregion
};
// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "ArcaneInputConfig.h"
#include "EnhancedInputComponent.h"
#include "ArcaneInputComponent.generated.h"

class UArcaneInputConfig;
UCLASS()
class ARCANE_API UArcaneInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UArcaneInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UArcaneInputComponent::BindAbilityActions(const UArcaneInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for(auto& [GameplayTag, InputAction] : InputConfig->AbilityInputActions)
	{
		if (!InputAction || !GameplayTag.IsValid())
		{
			continue;
		}

		if (PressedFunc)
		{
			BindAction(InputAction, ETriggerEvent::Started, Object, PressedFunc, GameplayTag);
		}

		if (ReleasedFunc)
		{
			BindAction(InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, GameplayTag);
		}

		if (HeldFunc)
		{
			BindAction(InputAction, ETriggerEvent::Triggered, Object, HeldFunc, GameplayTag);
		}
	}
}

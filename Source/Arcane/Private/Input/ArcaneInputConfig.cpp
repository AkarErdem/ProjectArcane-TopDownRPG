// Copyright (c) 2025 Erdem Akar

#include "Input/ArcaneInputConfig.h"
const UInputAction* UArcaneInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool LogNotFound) const
{
	if (!AbilityInputActions.Contains(InputTag))
	{
		if (LogNotFound)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
		}

		return nullptr;
	}

	return AbilityInputActions[InputTag];
}

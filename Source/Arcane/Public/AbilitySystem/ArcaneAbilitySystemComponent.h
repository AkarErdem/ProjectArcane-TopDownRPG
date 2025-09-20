// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ArcaneAbilitySystemComponent.generated.h"

UCLASS()
class ARCANE_API UArcaneAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BindGameplayEffectDelegates();

protected:
	void OnGameplayEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
};

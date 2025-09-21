// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ArcaneAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

UCLASS()
class ARCANE_API UArcaneAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BindGameplayEffectDelegates();

	FEffectAssetTags EffectAssetTags;

protected:
	void OnGameplayEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
};

// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAbilitySystemComponent.h"

void UArcaneAbilitySystemComponent::BindGameplayEffectDelegates()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UArcaneAbilitySystemComponent::OnGameplayEffectApplied);
}

void UArcaneAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(const TSubclassOf AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, /* InLevel */ 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UArcaneAbilitySystemComponent::OnGameplayEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}

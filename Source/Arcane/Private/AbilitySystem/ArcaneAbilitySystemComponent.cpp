// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAbilitySystemComponent.h"

void UArcaneAbilitySystemComponent::BindGameplayEffectDelegates()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UArcaneAbilitySystemComponent::OnGameplayEffectApplied);
}

void UArcaneAbilitySystemComponent::OnGameplayEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	for(const FGameplayTag& Tag : TagContainer)
	{
		//Broadcast tag to the Widget Controller
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, Msg);
		//OnGameplayEffectAppliedDelegateToSelf.Broadcast(ASC, EffectSpec, EffectHandle);
	}
}

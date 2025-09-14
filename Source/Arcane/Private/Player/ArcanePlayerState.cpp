// Copyright (c) 2025 Erdem Akar

#include "Player/ArcanePlayerState.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"

AArcanePlayerState::AArcanePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UArcaneAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UArcaneAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AArcanePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

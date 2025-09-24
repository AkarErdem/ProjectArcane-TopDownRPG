// Copyright (c) 2025 Erdem Akar

#include "Player/ArcanePlayerState.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

AArcanePlayerState::AArcanePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UArcaneAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UArcaneAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f);
}

void AArcanePlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AArcanePlayerState, Level);
}

UAbilitySystemComponent* AArcanePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AArcanePlayerState::OnRep_Level(int32 OldLevel) { }

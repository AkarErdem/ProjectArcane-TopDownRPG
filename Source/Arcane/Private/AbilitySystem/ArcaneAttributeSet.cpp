// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UArcaneAttributeSet::UArcaneAttributeSet()
{
	InitHealth(20.f);
	InitMaxHealth(100.f);
	InitMana(20.f);
	InitMaxMana(50.f);
}

void UArcaneAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Values are registered for replication here
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UArcaneAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, Health, OldHealth);
}

void UArcaneAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, MaxHealth, OldMaxHealth);
}

void UArcaneAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, Mana, OldMana);
}

void UArcaneAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, MaxMana, OldMaxMana);
}

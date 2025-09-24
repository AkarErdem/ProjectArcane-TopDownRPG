// Copyright (c) 2025 Erdem Akar

#include "Character/ArcaneCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"

AArcaneCharacterBase::AArcaneCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AArcaneCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AArcaneCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AArcaneCharacterBase::InitAbilityActorInfo() { }

void AArcaneCharacterBase::InitPrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);

	const FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, /*Level*/ 1, EffectContext);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data, GetAbilitySystemComponent());
}

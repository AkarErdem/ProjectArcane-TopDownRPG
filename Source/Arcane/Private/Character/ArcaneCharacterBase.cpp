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

void AArcaneCharacterBase::AddCharacterAbilities() const
{
	UArcaneAbilitySystemComponent* ArcaneASC = Cast<UArcaneAbilitySystemComponent>(GetAbilitySystemComponent());
	if (!HasAuthority())
	{
		return;
	}

	ArcaneASC->AddCharacterAbilities(StartupAbilities);
}

FVector AArcaneCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);

	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AArcaneCharacterBase::InitAbilityActorInfo() { }

void AArcaneCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data, GetAbilitySystemComponent());
}

void AArcaneCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes);
	ApplyEffectToSelf(DefaultSecondaryAttributes);
	ApplyEffectToSelf(DefaultVitalAttributes);
}

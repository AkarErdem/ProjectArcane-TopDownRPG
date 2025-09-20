// Copyright (c) 2025 Erdem Akar

#include "Character/ArcaneCharacterBase.h"
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

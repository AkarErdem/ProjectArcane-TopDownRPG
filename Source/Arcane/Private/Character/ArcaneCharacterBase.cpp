// Copyright (c) 2025 Erdem Akar


#include "Character/ArcaneCharacterBase.h"

AArcaneCharacterBase::AArcaneCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AArcaneCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

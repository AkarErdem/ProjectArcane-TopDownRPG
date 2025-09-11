// Copyright (c) 2025 Erdem Akar

#include "Character/ArcaneCharacterBase.h"

AArcaneCharacterBase::AArcaneCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AArcaneCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

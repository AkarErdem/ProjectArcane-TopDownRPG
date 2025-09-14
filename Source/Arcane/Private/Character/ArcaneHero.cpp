// Copyright (c) 2025 Erdem Akar

#include "Character/ArcaneHero.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ArcanePlayerState.h"

AArcaneHero::AArcaneHero()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400., 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AArcaneHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// GAS init (server side)
	InitAbilityActorInfo();
}

void AArcaneHero::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// GAS init (client side)
	InitAbilityActorInfo();
}

void AArcaneHero::InitAbilityActorInfo()
{
	AArcanePlayerState* ArcanePlayerState = GetPlayerState<AArcanePlayerState>();
	check(ArcanePlayerState);

	ArcanePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ArcanePlayerState, this);
	AbilitySystemComponent = Cast<UArcaneAbilitySystemComponent>(ArcanePlayerState->GetAbilitySystemComponent());
	AttributeSet = Cast<UArcaneAttributeSet>(ArcanePlayerState->GetAttributeSet());
}

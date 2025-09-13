// Copyright (c) 2025 Erdem Akar


#include "Character/ArcaneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AArcaneCharacter::AArcaneCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400., 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

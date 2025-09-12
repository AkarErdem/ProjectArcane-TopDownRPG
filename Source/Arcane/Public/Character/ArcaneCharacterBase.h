// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArcaneCharacterBase.generated.h"

UCLASS(Abstract)
class ARCANE_API AArcaneCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AArcaneCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};

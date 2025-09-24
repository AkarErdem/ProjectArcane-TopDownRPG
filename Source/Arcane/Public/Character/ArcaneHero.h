// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "Character/ArcaneCharacterBase.h"
#include "ArcaneHero.generated.h"

UCLASS()
class ARCANE_API AArcaneHero : public AArcaneCharacterBase
{
	GENERATED_BODY()

public:
	AArcaneHero();

	/** Server only */
	virtual void PossessedBy(AController* NewController) override;

	/** Client only */
	virtual void OnRep_PlayerState() override;

	virtual int32 GetCharacterLevel() override;

private:
	virtual void InitAbilityActorInfo() override;
};

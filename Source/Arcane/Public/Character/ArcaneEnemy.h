// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "Character/ArcaneCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "ArcaneEnemy.generated.h"

UCLASS()
class ARCANE_API AArcaneEnemy : public AArcaneCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AArcaneEnemy();

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface.

	//~ Begin IHighlight Interface.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;
	//~ End IHighlight Interface.
};

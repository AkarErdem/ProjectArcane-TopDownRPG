// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcaneEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class ARCANE_API AArcaneEffectActor : public AActor
{
	GENERATED_BODY()

protected:
	AArcaneEffectActor();

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};

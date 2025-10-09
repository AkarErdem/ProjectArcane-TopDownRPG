// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "ArcaneGameplayAbility.h"
#include "ArcaneProjectileSpell.generated.h"

class AArcaneProjectile;

UCLASS()
class ARCANE_API UArcaneProjectileSpell : public UArcaneGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AArcaneProjectile> ProjectileClass;
};

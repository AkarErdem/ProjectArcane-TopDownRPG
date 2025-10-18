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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AArcaneProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTarget);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};

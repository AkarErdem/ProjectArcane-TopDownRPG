// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "ArcaneCharacterBase.generated.h"

class UMotionWarpingComponent;
class UGameplayAbility;
class UGameplayEffect;
class UArcaneAttributeSet;
class UAttributeSet;
class UArcaneAbilitySystemComponent;

UCLASS(Abstract)
class ARCANE_API AArcaneCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AArcaneCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}

protected:
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName = "";

	UPROPERTY()
	TObjectPtr<UArcaneAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, const float Level = 1.f) const;

	void InitDefaultAttributes() const;

	void AddCharacterAbilities() const;

	virtual void InitAbilityActorInfo();

	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

	//~ Begin UCombat Interface
	virtual FVector GetSocketLocation() override;
	virtual void UpdateFacingTarget_Implementation(FName TargetName, FVector TargetLocation) override;
	//~ End UCombat Interface

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};

// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/ArcaneCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "ArcaneEnemy.generated.h"

enum ECharacterClass : uint8;
class UWidgetComponent;

UCLASS()
class ARCANE_API AArcaneEnemy : public AArcaneCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AArcaneEnemy();

	//~ Begin IHighlight Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;
	//~ End IHighlight Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnMaxHealthChanged;

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface

	//~ Begin ICombat Interface
	FORCEINLINE virtual int32 GetCharacterLevel() override
	{
		return Level;
	}

	//~ End ICombat Interface

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Defaults")
	TEnumAsByte<ECharacterClass> CharacterClass = Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool IsHitReacting;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float BaseWalkSpeed = 250.f;

	virtual void InitDefaultAttributes() const override;

private:
	FDelegateHandle HealthChangedHandle;
	FDelegateHandle MaxHealthChangedHandle;

	void InitializeEnemy();

	void CleanupEnemy();

	void OnHitReactTagChanged(const FGameplayTag Tag, int32 Count);

	void UpdateWalkSpeed() const;
};

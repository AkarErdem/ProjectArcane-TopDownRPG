// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ArcaneAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeDelegate);

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() { }

	FGameplayEffectContextHandle Context;

	UPROPERTY()
	UAbilitySystemComponent* ASC = nullptr;

	UPROPERTY()
	AActor* AvatarActor = nullptr;

	UPROPERTY()
	AController* Controller = nullptr;

	UPROPERTY()
	ACharacter* Character = nullptr;
};

UCLASS()
class ARCANE_API UArcaneAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UArcaneAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Called after a gameplay effect has already been applied. */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*
	 * Vital Attributes
	 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Health);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Mana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, MaxMana);

	/*
	 * Primary Attributes
	 */
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Strength);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Intelligence);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Resilience);

	UFUNCTION()
	void OnRep_Vitality(const FGameplayAttributeData& OldVitality);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vitality, Category="Primary Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Vitality);

	/*
	 * Secondary Attributes
	 */
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category="Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, Armor);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, ArmorPenetration);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, BlockChance);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, CriticalHitChance);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, CriticalHitDamage);

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, CriticalHitResistance);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, HealthRegeneration);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UArcaneAttributeSet, ManaRegeneration);

private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Source, FEffectProperties& Target);
};

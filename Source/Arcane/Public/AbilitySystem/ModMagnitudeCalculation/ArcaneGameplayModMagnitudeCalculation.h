// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ArcaneGameplayModMagnitudeCalculation.generated.h"

USTRUCT(BlueprintType)
struct FAttributeCoefficient
{
	GENERATED_BODY()
	FAttributeCoefficient() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Coefficient = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ValidEnumValues="AddBase, MultiplyAdditive, DivideAdditive"))
	TEnumAsByte<EGameplayModOp::Type> Operation = EGameplayModOp::AddBase;
};

/**
 * Mod Magnitude Calculation Base Class
 */
UCLASS()
class ARCANE_API UArcaneGameplayModMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UArcaneGameplayModMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	UPROPERTY(EditAnywhere)
	float BaseValue = 1.f;

	UPROPERTY(EditAnywhere)
	float LevelMultiplier = 10.f;

	UPROPERTY(EditAnywhere)
	TArray<FAttributeCoefficient> AttributeCoefficients;
};

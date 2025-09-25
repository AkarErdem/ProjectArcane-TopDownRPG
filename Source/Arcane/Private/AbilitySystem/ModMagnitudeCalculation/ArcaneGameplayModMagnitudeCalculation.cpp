// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ModMagnitudeCalculation/ArcaneGameplayModMagnitudeCalculation.h"
#include "Interaction/CombatInterface.h"

UArcaneGameplayModMagnitudeCalculation::UArcaneGameplayModMagnitudeCalculation() { }

float UArcaneGameplayModMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 CharacterLevel = CombatInterface->GetCharacterLevel();

	float AttributeContribution = 0.f;
	for(FAttributeCoefficient AttributeCoefficient : AttributeCoefficients)
	{
		if(const FGameplayEffectAttributeCaptureDefinition* CapturedAttribute = RelevantAttributesToCapture.
			FindByPredicate([AttributeCoefficient](const FGameplayEffectAttributeCaptureDefinition& Item)
			{
				return Item.AttributeToCapture.AttributeName == AttributeCoefficient.Attribute.AttributeName;
			}))
		{
			FAggregatorEvaluateParameters EvalParams;
			float AttValue = 0.f;
			GetCapturedAttributeMagnitude(*CapturedAttribute, Spec, EvalParams, AttValue);
			AttValue = FMath::Max<float>(AttValue, 0.f);
			switch(AttributeCoefficient.Operation)
			{
			case EGameplayModOp::AddBase:
				AttributeContribution += (AttributeCoefficient.Coefficient + AttValue);
				break;
			case EGameplayModOp::MultiplyAdditive:
				AttributeContribution += (AttributeCoefficient.Coefficient * AttValue);
				break;
			case EGameplayModOp::DivideAdditive:
				AttributeContribution += (AttributeCoefficient.Coefficient / AttValue);
				break;
			default:
				break;
			}
		}
	}

	// BaseValue + Coefficient1*Attribute1 ... + LevelMultiplier * CharacterLevel
	return BaseValue + AttributeContribution + LevelMultiplier * CharacterLevel;
}

// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FArcaneAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;

	FArcaneAttributeInfo() = default;
};

UCLASS()
class ARCANE_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FArcaneAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, const bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, FArcaneAttributeInfo> AttributeInformation;
};

// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute AttributeGetter = FGameplayAttribute();
};

UCLASS()
class ARCANE_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FArcaneAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, const bool bLogNotFound = false) const;

#if WITH_EDITOR
	UFUNCTION(Category="Populate Attribute Info", CallInEditor)
	void PopulateDataAsset();
#endif

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="AttributeName"))
	TArray<FArcaneAttributeInfo> AttributeInformation;
};

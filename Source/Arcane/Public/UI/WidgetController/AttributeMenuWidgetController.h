// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ArcaneWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FGameplayAttribute;
struct FGameplayTag;
struct FArcaneAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryAttributeChangedDelegate, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoDelegate, const FArcaneAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class ARCANE_API UAttributeMenuWidgetController : public UArcaneWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoDelegate AttributeInfoChanged;

protected:
	UPROPERTY(EditDefaultsOnly, Category="GAS|Attributes")
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& Tag) const;
};

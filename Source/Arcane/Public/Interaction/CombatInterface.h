// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class ARCANE_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetCharacterLevel();

	virtual FVector GetSocketLocation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	void UpdateFacingTarget(FName TargetName, FVector TargetLocation);
};

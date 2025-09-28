// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Player/ArcanePlayerState.h"
#include "UI/HUD/ArcaneHUD.h"
#include "UI/WidgetController/ArcaneWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "ArcaneAbilitySystemLibrary.generated.h"

UCLASS()
class ARCANE_API UArcaneAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="ArcaneAbilitySystemLibrary|WidgetController", meta = (WorldContext = "WorldContextObject"))
	static UArcaneWidgetController* GetArcaneOverlayWidgetController(const UObject* WorldContextObject)
	{
		if(const APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
		{
			if(AArcaneHUD* ArcaneHUD = Cast<AArcaneHUD>(PC->GetHUD()))
			{
				if(FWidgetControllerData WidgetControllerData; GetWidgetControllerData(WorldContextObject, WidgetControllerData))
				{
					return ArcaneHUD->GetOverlayWidgetController(WidgetControllerData);
				}
			}
		}
		return nullptr;
	}

	UFUNCTION(BlueprintPure, Category="ArcaneAbilitySystemLibrary|WidgetController", meta = (WorldContext = "WorldContextObject"))
	static UArcaneWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject)
	{
		if(const APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
		{
			if(AArcaneHUD* ArcaneHUD = Cast<AArcaneHUD>(PC->GetHUD()))
			{
				if(FWidgetControllerData WidgetControllerData; GetWidgetControllerData(WorldContextObject, WidgetControllerData))
				{
					return ArcaneHUD->GetAttributeMenuWidgetController(WidgetControllerData);
				}
			}
		}
		return nullptr;
	}

	[[nodiscard]] static bool GetWidgetControllerData(const UObject* WorldContextObject, OUT FWidgetControllerData& OutData)
	{
		if(APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
		{
			AArcanePlayerState* PS = PC->GetPlayerState<AArcanePlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			OutData = FWidgetControllerData(PC, PS, ASC, AS);
			return true;
		}
		return false;
	}
};

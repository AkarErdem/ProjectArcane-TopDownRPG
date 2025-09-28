// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAbilitySystemLibrary.h"

bool UArcaneAbilitySystemLibrary::MakeWidgetControllerData(const UObject* WorldContextObject, FWidgetControllerData& OutWidgetControllerData, AArcaneHUD*& OutArcaneHUD)
{
	if (APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController())
	{
		OutArcaneHUD = Cast<AArcaneHUD>(PC->GetHUD());
		if (OutArcaneHUD)
		{
			AArcanePlayerState* PS = PC->GetPlayerState<AArcanePlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWidgetControllerData.AttributeSet = AS;
			OutWidgetControllerData.AbilitySystemComponent = ASC;
			OutWidgetControllerData.PlayerState = PS;
			OutWidgetControllerData.PlayerController = PC;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UArcaneAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	AArcaneHUD* ArcaneHUD = nullptr;
	if (FWidgetControllerData WidgetControllerData; MakeWidgetControllerData(WorldContextObject, WidgetControllerData, ArcaneHUD))
	{
		return ArcaneHUD->GetOverlayWidgetController(WidgetControllerData);
	}
	return nullptr;
}

UAttributeMenuWidgetController* UArcaneAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	AArcaneHUD* ArcaneHUD = nullptr;
	if (FWidgetControllerData WidgetControllerData; MakeWidgetControllerData(WorldContextObject, WidgetControllerData, ArcaneHUD))
	{
		return ArcaneHUD->GetAttributeMenuWidgetController(WidgetControllerData);
	}
	return nullptr;
}
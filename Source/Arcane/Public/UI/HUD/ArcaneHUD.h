// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/ArcaneWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "ArcaneHUD.generated.h"

class UArcaneUserWidget;
struct FWidgetControllerData;

UCLASS()
class ARCANE_API AArcaneHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerData& Data)
	{
		return GetOrCreateWidgetController<UOverlayWidgetController>(OverlayWidgetController, OverlayWidgetControllerClass, Data);
	}

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerData& Data)
	{
		return GetOrCreateWidgetController<UAttributeMenuWidgetController>(AttributeMenuWidgetController, AttributeMenuWidgetControllerClass, Data);
	}

private:
	UPROPERTY()
	TObjectPtr<UArcaneUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UArcaneUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UArcaneUserWidget> AttributeMenuWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UArcaneUserWidget> AttributeMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	template<typename TWidgetController = UArcaneWidgetController>
	TWidgetController* GetOrCreateWidgetController(TObjectPtr<TWidgetController>& Cached, const TSubclassOf<TWidgetController> ControllerClass, const FWidgetControllerData& Data)
	{
		check(*ControllerClass); // Fail if class isn’t set in editor

		if(Cached == nullptr)
		{
			Cached = NewObject<TWidgetController>(this, ControllerClass);
			check(Cached);

			Cached->SetWidgetControllerData(Data);
			Cached->BindCallbacksToDependencies();
		}
		return Cached.Get();
	}
};

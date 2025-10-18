// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArcaneUserWidget.generated.h"

UCLASS()
class ARCANE_API UArcaneUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};

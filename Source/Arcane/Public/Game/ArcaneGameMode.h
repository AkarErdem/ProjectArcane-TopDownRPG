// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcaneGameMode.generated.h"

class UCharacterClassInfo;

UCLASS()
class ARCANE_API AArcaneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};

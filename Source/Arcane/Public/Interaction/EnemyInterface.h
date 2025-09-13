// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightInterface.h"
#include "EnemyInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyInterface : public UHighlightInterface
{
	GENERATED_BODY()
};

class ARCANE_API IEnemyInterface : public IHighlightInterface
{
	GENERATED_BODY()
};

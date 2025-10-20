// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAbilitySystemLibrary.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/ArcaneGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ArcanePlayerState.h"

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

void UArcaneAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	const AArcaneGameMode* ArcaneGameMode = Cast<AArcaneGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));

	if (!ArcaneGameMode)
	{
		return;
	}

	const TObjectPtr<UCharacterClassInfo> CharacterClassInfo = ArcaneGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo CharacterClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	const AActor* AvatarActor = ASC->GetAvatarActor();

	FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
	PrimaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
	SecondaryAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
	VitalAttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataUnderMouse = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return TargetDataUnderMouse;
}

void UTargetDataUnderMouse::Activate()
{
	if(Ability->IsLocallyControlled())
	{
		SendTargetDataToServer();
	}
	// We are on the server, so listen for target data
	else
	{
		ReceiveTargetDataFromClient();
	}
}

void UTargetDataUnderMouse::SendTargetDataToServer()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	const APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	// Note: These are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr)
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Data->HitResult);

	const FGameplayAbilityTargetDataHandle DataHandle = FGameplayAbilityTargetDataHandle(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::ReceiveTargetDataFromClient()
{
	const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
	const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

	AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey)
						  .AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

	const bool CalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
	if (!CalledDelegate)
	{
		SetWaitingOnRemotePlayerData();
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

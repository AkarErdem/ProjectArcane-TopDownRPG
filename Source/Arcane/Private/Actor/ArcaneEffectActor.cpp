// Copyright (c) 2025 Erdem Akar

#include "Actor/ArcaneEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AArcaneEffectActor::AArcaneEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
}

void AArcaneEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		UE_LOG(LogTemp, Error, TEXT("in: %s"), *this->GetName());
		check(GameplayEffectClass);

		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(
			GameplayEffectClass, 1.0f, EffectContext);
		const FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToTarget(
			*EffectSpecHandle.Data, ASC);

		if (EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite &&
			InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			AppliedEffects.Add(ActiveEffectHandle, TWeakObjectPtr(ASC));
		}
	}
}

void AArcaneEffectActor::RemoveEffectFromTarget(AActor* TargetActor)
{
	if (const UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		UE_LOG(LogTemp, Error, TEXT("out: %s"), *this->GetName());

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto& Pair : AppliedEffects)
		{
			if (!Pair.Value.IsValid() || Pair.Value != ASC)
			{
				continue;
			}
			Pair.Value->RemoveActiveGameplayEffect(Pair.Key);
			HandlesToRemove.Add(Pair.Key);
		}
		for (FActiveGameplayEffectHandle& ToRemove : HandlesToRemove)
		{
			AppliedEffects.Remove(ToRemove);
		}
	}
}

void AArcaneEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectPolicy == EEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectPolicy == EEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectPolicy == EEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AArcaneEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectPolicy == EEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectPolicy == EEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectPolicy == EEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveEffectFromTarget(TargetActor);
	}
}

// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "MathUtil.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UArcaneAttributeSet::UArcaneAttributeSet()
{
	InitHealth(10.f);
	InitMaxHealth(100.f);
	InitMana(0.f);
	InitMaxMana(100.f);
}

void UArcaneAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Values are registered for replication here
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UArcaneAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UArcaneAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Source;
	FEffectProperties Target;
	SetEffectProperties(Data, Source, Target);

	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	if(Attribute == GetHealthAttribute())
	{
		SetHealth(FMathf::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if(Attribute == GetManaAttribute())
	{
		SetMana(FMathf::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UArcaneAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, Health, OldHealth);
}

void UArcaneAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, MaxHealth, OldMaxHealth);
}

void UArcaneAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, Mana, OldMana);
}

void UArcaneAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, MaxMana, OldMaxMana);
}

void UArcaneAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Source,
                                              FEffectProperties& Target)
{
	const FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	if(!IsValid(SourceASC))
	{
		return;
	}

	AActor* SourceAvatarActor = SourceASC->GetAvatarActor();
	if(!IsValid(SourceAvatarActor))
	{
		return;
	}

	AController* SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();
	if(APawn* Pawn = Cast<APawn>(SourceAvatarActor); !SourceController)
	{
		if(!IsValid(Pawn))
		{
			return;
		}
		SourceController = Pawn->GetController();
	}

	if(!IsValid(SourceController))
	{
		return;
	}

	ACharacter* SourceCharacter = SourceController->GetCharacter();
	if(!IsValid(SourceCharacter))
	{
		return;
	}

	if(!Data.Target.AbilityActorInfo.IsValid() || !Data.Target.GetAvatarActor())
	{
		return;
	}

	AActor* TargetAvatarActor = Data.Target.GetAvatarActor();
	AController* TargetController = Data.Target.AbilityActorInfo.Get()->PlayerController.Get();
	ACharacter* TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);

	Source.ASC = SourceASC;
	Source.AvatarActor = SourceAvatarActor;
	Source.Controller = SourceController;
	Source.Character = SourceCharacter;

	Target.ASC = TargetASC;
	Target.AvatarActor = TargetAvatarActor;
	Target.Controller = TargetController;
	Target.Character = TargetCharacter;
}

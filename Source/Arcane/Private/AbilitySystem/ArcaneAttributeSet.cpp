// Copyright (c) 2025 Erdem Akar

#include "AbilitySystem/ArcaneAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "MathUtil.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UArcaneAttributeSet::UArcaneAttributeSet()
{
	InitHealth(50.f);
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

	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcaneAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
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

#define ON_REP_ATTRIBUTE(AttributeName) \
void UArcaneAttributeSet::OnRep_##AttributeName(const FGameplayAttributeData& Old##AttributeName) \
{ \
GAMEPLAYATTRIBUTE_REPNOTIFY(UArcaneAttributeSet, AttributeName, Old##AttributeName); \
}

ON_REP_ATTRIBUTE(Health);
ON_REP_ATTRIBUTE(MaxHealth);
ON_REP_ATTRIBUTE(Mana);
ON_REP_ATTRIBUTE(MaxMana);

ON_REP_ATTRIBUTE(Strength);
ON_REP_ATTRIBUTE(Intelligence);
ON_REP_ATTRIBUTE(Defense);
ON_REP_ATTRIBUTE(Vitality);

#undef ON_REP_ATTRIBUTE

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

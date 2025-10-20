// Copyright (c) 2025 Erdem Akar

#include "Character/ArcaneEnemy.h"
#include "AbilitySystem/ArcaneAbilitySystemComponent.h"
#include "AbilitySystem/ArcaneAbilitySystemLibrary.h"
#include "AbilitySystem/ArcaneAttributeSet.h"
#include "Arcane/Arcane.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/ArcaneUserWidget.h"

AArcaneEnemy::AArcaneEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UArcaneAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UArcaneAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AArcaneEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeEnemy();
}

void AArcaneEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanupEnemy();
	Super::EndPlay(EndPlayReason);
}

void AArcaneEnemy::InitDefaultAttributes() const
{
	Super::InitDefaultAttributes();

	UArcaneAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, GetAbilitySystemComponent());
}

void AArcaneEnemy::InitializeEnemy()
{
	InitAbilityActorInfo();

	if (UArcaneUserWidget* ArcaneUserWidget = Cast<UArcaneUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		ArcaneUserWidget->SetWidgetController(this);
	}

	if(const UArcaneAttributeSet* ArcaneAttributeSet = CastChecked<UArcaneAttributeSet>(AttributeSet))
	{
		 HealthChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});

		 MaxHealthChangedHandle =AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		OnHealthChanged.Broadcast(ArcaneAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(ArcaneAttributeSet->GetMaxHealth());
	}
}
void AArcaneEnemy::CleanupEnemy()
{
	if (const UArcaneAttributeSet* ArcaneAttributeSet = CastChecked<UArcaneAttributeSet>(AttributeSet); ArcaneAttributeSet && AbilitySystemComponent)
	{
		if (HealthChangedHandle.IsValid())
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetHealthAttribute()).Remove(HealthChangedHandle);
			HealthChangedHandle.Reset();
		}

		if (MaxHealthChangedHandle.IsValid())
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ArcaneAttributeSet->GetMaxHealthAttribute()).Remove(MaxHealthChangedHandle);
			MaxHealthChangedHandle.Reset();
		}
	}
}

void AArcaneEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->BindGameplayEffectDelegates();

	InitDefaultAttributes();
}

void AArcaneEnemy::HighlightActor()
{
	bHighlighted = true;
	for(TInlineComponentArray<UMeshComponent*> Meshes(this, /*bIncludeFromChildActors*/ true); auto* M : Meshes)
	{
		M->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
		M->SetRenderCustomDepth(true);
	}
}

void AArcaneEnemy::UnHighlightActor()
{
	bHighlighted = false;
	for(TInlineComponentArray<UMeshComponent*> Meshes(this, /*bIncludeFromChildActors*/ true); auto* M : Meshes)
	{
		M->SetRenderCustomDepth(false);
	}
}

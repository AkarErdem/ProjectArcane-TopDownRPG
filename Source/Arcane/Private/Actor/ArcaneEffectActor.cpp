// Copyright (c) 2025 Erdem Akar

#include "Actor/ArcaneEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ArcaneAttributeSet.h"
#include "Components/SphereComponent.h"

AArcaneEffectActor::AArcaneEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AArcaneEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AArcaneEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AArcaneEffectActor::OnEndOverlap);
}

void AArcaneEffectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Sphere->OnComponentBeginOverlap.RemoveDynamic(this, &AArcaneEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.RemoveDynamic(this, &AArcaneEffectActor::OnEndOverlap);
}

void AArcaneEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Added for testing, refactor here to use gameplay effect
	if (const IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAbilitySystemComponent* ASC = ASCInterface->GetAbilitySystemComponent();
		const UArcaneAttributeSet* ArcaneAttributeSet = Cast<UArcaneAttributeSet>(ASC->GetAttributeSet(UArcaneAttributeSet::StaticClass()));
		UArcaneAttributeSet* MutableArcaneAttributeSet = const_cast<UArcaneAttributeSet*>(ArcaneAttributeSet);
		MutableArcaneAttributeSet->SetHealth(MutableArcaneAttributeSet->GetHealth() + 50.f);
		MutableArcaneAttributeSet->SetMana(MutableArcaneAttributeSet->GetMana() - 25.f);

		Destroy();
	}
}

void AArcaneEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

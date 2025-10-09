// Copyright (c) 2025 Erdem Akar

#include "Actor/ArcaneProjectile.h"
#include "Actor/ArcaneProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArcaneProjectile::AArcaneProjectile()
{
 	PrimaryActorTick.bCanEverTick = false;
 	bReplicates = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SetRootComponent(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	// ProjectileMovement->bRotationFollowsVelocity = true;
	// ProjectileMovement->bShouldBounce = false;
}

void AArcaneProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AArcaneProjectile::OnSphereOverlap);
}

void AArcaneProjectile::OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


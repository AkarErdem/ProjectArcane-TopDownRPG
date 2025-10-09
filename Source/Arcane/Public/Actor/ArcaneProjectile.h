// Copyright (c) 2025 Erdem Akar

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcaneProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ARCANE_API AArcaneProjectile : public AActor
{
	GENERATED_BODY()

public:
	AArcaneProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};

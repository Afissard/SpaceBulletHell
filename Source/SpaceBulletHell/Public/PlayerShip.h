// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShip.h"
#include "PlayerMissile.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API APlayerShip : public ASpaceShip
{
	GENERATED_BODY()

	int PlayerScore = 0;

public:
	APlayerShip();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	FTimerHandle FireTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float FireInterval = 0.2f; // Intervalle entre tirs
	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<APlayerMissile> PlayerMissileClass;

	void StartFireMissile();
	void StopFireMissile();
	virtual void FireProjectile() override;
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;
};

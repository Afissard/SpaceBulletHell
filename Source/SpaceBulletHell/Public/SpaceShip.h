// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UFO.h"
#include "SpaceShip.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API ASpaceShip : public AUFO
{
	GENERATED_BODY()

public:
	ASpaceShip();
	
protected:
	virtual void BeginPlay() override;

public:
	// Accélération appliquée lors de la poussée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Missile")
	TSubclassOf<class AMissile> MissileClass;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void ThrustForward(float Value);
	UFUNCTION()
	void ThrustRight(float Value);
	UFUNCTION()
	void FireProjectile();
	
};

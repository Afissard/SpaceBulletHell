// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UFO.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API APlayerShip : public AUFO
{
	GENERATED_BODY()

	int PlayerScore = 0;

public:
	APlayerShip();

protected:
	virtual void BeginPlay() override;
	
	// Accélération appliquée lors de la poussée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration = 500.0f;

	// Vitesse de rotation du vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnSpeed = 100.0f;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ThrustForward(float Value);
	UFUNCTION()
	void ThrustRight(float Value);
	UFUNCTION()
	void FireProjectile();
};

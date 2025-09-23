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

protected:
	// Accélération appliquée lors de la poussée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration = 1000.0f;

	// Vitesse de rotation du vaisseau
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnSpeed = 100.0f;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void ThrustForward(float Value);
	void TurnRight(float Value);
};

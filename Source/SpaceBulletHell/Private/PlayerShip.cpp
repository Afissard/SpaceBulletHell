// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"

APlayerShip::APlayerShip()
	: AUFO() // Appelle le constructeur parent
{
	SphereCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	// Game variables
	MaxHealth = 5;
	Health = MaxHealth;
	DamagePower = 1;
	ScoreValue = 0;
	
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShip::ThrustForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerShip::TurnRight);
}

void APlayerShip::ThrustForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector Force = GetActorForwardVector() * Value * Acceleration;
		SpaceMovementApplyForce(Force);
	}
}

void APlayerShip::TurnRight(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value * TurnSpeed * GetWorld()->GetDeltaSeconds());
	}
}

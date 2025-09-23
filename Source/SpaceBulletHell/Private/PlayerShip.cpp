// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"

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

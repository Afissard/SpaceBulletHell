// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

/*
FVector AUFO::Seek()
{
	// 1. calculate the desired velocity
	FVector vDesired = vTarget - vPosition;
	// 2. normalize the desired velocity
	vDesired.Normalize();
	// 3. scale the desired velocity to the maximum speed
	vDesired *= dMaxSpeed;
	// 4. calculate the steering force
	FVector vSteering = vDesired - vVelocity;
	// 5. Limit Steering force to Max speed
	vSteering = vSteering.GetClampedToMaxSize(dMaxSpeed);
	vSteering.Z = 0.0f; // Keep movement in the XY plane
	return vSteering;
}
*/

void AMissile::AMssile()
{
	SphereCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
}

void AMissile::Init(FVector newInertia)
{
	Inertia = newInertia;
	MaxHealth = 1;
	Health = MaxHealth;
	DamagePower = 2;
	ScoreValue = 0;
}

void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SpaceMovementApplyForce(FVector(0.f, 0.f, 0.f));
}
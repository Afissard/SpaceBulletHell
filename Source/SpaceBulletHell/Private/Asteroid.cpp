// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"


void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Asteroid spawned at: %s"), *GetActorLocation().ToString());

	// Set vTarget to a position behind the player (get a point around the player and trace a line and follow this
	// direction forever until it reach world end)
	float Angle = FMath::RandRange(0.f, 2 * PI);
	float Speed = FMath::RandRange(300.f, 600.f);
	Inertia = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * Speed;
}

void AAsteroid::Tick(float DeltaTime)
{

	FVector OldLocation = GetActorLocation();

	Super::Tick(DeltaTime);
	
	SpaceMovementApplyForce(FVector(0.f, 0.f, 0.f));
	FVector NewLocation = GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("%s moved %.2f units"), *GetActorNameOrLabel(),  (NewLocation - OldLocation).Size());
}
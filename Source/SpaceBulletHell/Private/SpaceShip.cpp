// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Asteroid.h"
#include "GameMaster.h"
#include "Missile.h"
#include "Kismet/GameplayStatics.h"

ASpaceShip::ASpaceShip(): AUFO()
{
	SphereCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
}

void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
	// Game variables
	MaxHealth = 5;
	Health = MaxHealth;
	DamagePower = 0;
	ScoreValue = 0;

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShip::OnOverlap);
}

void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Only for the player
	FVector Location = GetActorLocation();
	float WorldLimitX = 750.f;
	float WorldLimitY = 1300.f;

	if (
		FMath::Abs(Location.X) > WorldLimitX ||
		FMath::Abs(Location.Y) > WorldLimitY ||
		FMath::Abs(Location.X) < WorldLimitX*(-1) ||
		FMath::Abs(Location.Y) < WorldLimitY*(-1)
		)
	{
		SetActorLocation(FVector(0.f, 0.f, Location.Z));
		Health -= 1;
	}

	/*
	if (Health <= 0)
	{
		Destroy();
	}
	*/
}

void ASpaceShip::ThrustForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector Force = GetActorForwardVector() * Value * Acceleration;
		SpaceMovementApplyForce(Force);
	}
}

void ASpaceShip::ThrustRight(float Value)
{
	if (Value != 0.0f)
	{
		FVector Force = GetActorRightVector() * Value * Acceleration;
		SpaceMovementApplyForce(Force);
	}
}

void ASpaceShip::FireProjectile()
{
	ASpaceShip* Player = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player) return;

	FVector Forward = Player->GetActorForwardVector();
	FVector SpawnLocation = Player->GetActorLocation() + Forward * 75.f;

	FVector MissileInertia = FVector(1.f, 0.f, 0.f) * 20.f;

	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;

	AMissile* NewMissile = GetWorld()->SpawnActor<AMissile>(MissileClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (NewMissile)
	{
		NewMissile->Init(MissileInertia);
	}
}

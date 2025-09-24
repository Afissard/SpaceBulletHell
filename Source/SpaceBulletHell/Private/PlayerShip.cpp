// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"

#include "Missile.h"
#include "Kismet/GameplayStatics.h"

APlayerShip::APlayerShip()
	: AUFO() // Appelle le constructeur parent
{
	SphereCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	
	// Game variables
	MaxHealth = 5;
	Health = MaxHealth;
	DamagePower = 1;
	ScoreValue = 0;
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShip::ThrustForward);
	PlayerInputComponent->BindAxis("ThrustRight", this, &APlayerShip::ThrustRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::FireProjectile);
}

void APlayerShip::ThrustForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector Force = GetActorForwardVector() * Value * Acceleration;
		SpaceMovementApplyForce(Force);
	}
}

void APlayerShip::ThrustRight(float Value)
{
	if (Value != 0.0f)
	{
		FVector Force = GetActorRightVector() * Value * Acceleration;
		SpaceMovementApplyForce(Force);
	}
}

void APlayerShip::FireProjectile()
{
	APlayerShip* Player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"


void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Asteroid spawned at: %s"), *GetActorLocation().ToString());

	// Take random coordinate around the player and go toward these
	//float Angle = FMath::RandRange(0.f, 2 * PI);
	//float Speed = FMath::RandRange(300.f, 600.f);
	//Inertia = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * Speed;

	// Récupère la position du joueur
	APlayerShip* Player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player) return;

	FVector PlayerLocation = Player->GetActorLocation();

	// Choisit un angle aléatoire autour du joueur
	float Angle = FMath::RandRange(0.f, 2 * PI);
	float SpawnDistance = FMath::RandRange(2000.f, 3000.f); // Distance éloignée

	// Calcule la position de spawn autour du joueur
	FVector SpawnOffset = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * SpawnDistance;
	FVector SpawnLocation = PlayerLocation + SpawnOffset;
	SetActorLocation(SpawnLocation);

	// Choisit un point cible proche du joueur
	float TargetRadius = FMath::RandRange(0.f, 300.f);
	float TargetAngle = FMath::RandRange(0.f, 2 * PI);
	FVector TargetOffset = FVector(FMath::Cos(TargetAngle), FMath::Sin(TargetAngle), 0.f) * TargetRadius;
	FVector TargetLocation = PlayerLocation + TargetOffset;

	// Calcule la direction vers le point cible
	FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
	float Speed = FMath::RandRange(0.01f, 1.f);
	Inertia = Direction * Speed;

	// Game variables
	Health = FMath::RandRange(1, 3);
	MaxHealth = Health;
	DamagePower = Health; // Plus l'asteroide est gros, plus il fait
	ScoreValue = Health * 10;
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SpaceMovementApplyForce(FVector(0.f, 0.f, 0.f));
}
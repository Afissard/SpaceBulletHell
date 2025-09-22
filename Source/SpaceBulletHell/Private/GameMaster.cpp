// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMaster.h"

// Sets default values
AGameMaster::AGameMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn >= 1.f) {
		spawnAsteroid();
		TimeSinceLastSpawn = 0.f;
	}

}

void AGameMaster::spawnAsteroid()
{
	FVector SpawnLocation(
		FMath::RandRange(-1000.f, 1000.f),
		FMath::RandRange(-1000.f, 1000.f),
		0.f
	);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnLocation, SpawnRotation);
}

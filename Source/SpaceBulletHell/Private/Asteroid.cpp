// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"


void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Asteroid spawned at: %s"), *GetActorLocation().ToString());
}

void AAsteroid::Init(FVector newInertia, int newMaxHealth)
{
	Inertia = newInertia;
	MaxHealth = newMaxHealth;
	Health = MaxHealth;
	DamagePower = MaxHealth; // Plus l'asteroide est gros, plus il fait
	ScoreValue = MaxHealth * 10;
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SpaceMovementApplyForce(FVector(0.f, 0.f, 0.f));
}
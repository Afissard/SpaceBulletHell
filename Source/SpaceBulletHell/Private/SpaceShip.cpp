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

	AGameMaster* GM = Cast<AGameMaster>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameMaster::StaticClass()));
	if (GM)
	{
		ProjectilesTraites.Add(GM);
	}
	
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

	if (InvincibilityTimer > 0.f)
	{
		InvincibilityTimer -= DeltaTime;
	}
	
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
	
}

void ASpaceShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   )
{
	if (OtherActor && OtherActor != this && InvincibilityTimer <= 0.f && !ProjectilesTraites.Contains(OtherActor))
	{
		
		if (ProjectilesTraites.Contains(OtherActor))
		{
			ProjectilesTraites.Add(OtherActor);
			InvincibilityTimer = InvincibilityTime;
		}
	}
}

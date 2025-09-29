// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

#include "Asteroid.h"
#include "EnemyShip.h"
#include "PlayerShip.h"

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

void AMissile::Init(FVector newInertia, bool spawnedByPlayer)
{
	Inertia = newInertia;
	MaxHealth = 1;
	Health = MaxHealth;
	DamagePower = 2;
	ScoreValue = 0;
	IsSpawnedByPlayer = spawnedByPlayer;
}

void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMissile::OnOverlap);
}

void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SpaceMovementApplyForce(FVector(0.f, 0.f, 0.f));

	if (ToBeDestroyedNextFrame)
	{
		Destroy();
	}
}

void AMissile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s collided with : %s"), *GetActorNameOrLabel(), *OtherActor->GetName());

		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			if (AAsteroid* AsteroidUFO = Cast<AAsteroid>(OtherUFO))
			{
				ToBeDestroyedNextFrame = true;

				// FIX: Mask the hitbox issues
				//DamagePower = 0; // Prevents double damage if multiple collisions in the same frame
			}

			if (IsSpawnedByPlayer)
			{
				if (AEnemyShip* EnemyShipUFO = Cast<AEnemyShip>(OtherUFO))
				{
					ToBeDestroyedNextFrame = true;
				}
			} else
			{
				if (APlayerShip* PlayerShipUFO = Cast<APlayerShip>(OtherUFO))
				{
					ToBeDestroyedNextFrame = true;
				}
			}
		}
	}
}

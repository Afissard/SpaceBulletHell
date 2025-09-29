// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMissile.h"

#include "Asteroid.h"
#include "EnemyShip.h"
#include "Missile.h"
#include "PlayerShip.h"

APlayerMissile::APlayerMissile(): AMissile()
{
	
}
	
void APlayerMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerMissile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

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

			if (AEnemyShip* EnemyShipUFO = Cast<AEnemyShip>(OtherUFO))
			{
				ToBeDestroyedNextFrame = true;
			}
		}
	}
}

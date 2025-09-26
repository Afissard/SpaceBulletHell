// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"

#include "GameMaster.h"
#include "Missile.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"

AEnemyShip::AEnemyShip()
{
	SphereCollision->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	
	// Game variables
	MaxHealth = 20;
	Health = MaxHealth;
	DamagePower = 100; // dissuasion
	ScoreValue = 0;

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyShip::OnOverlap);
}

void AEnemyShip::Tick(float DeltaTime)
{

	if (Health <= 0)
	{
		Kill();
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("BOSS position %s"), *GetActorLocation().ToString());
	
	if (GetActorLocation().Y > 500.f)
	{
		goRight = true;
	} else if (GetActorLocation().Y < -500.f)
	{
		goRight = false;
	}

	if (goRight)
	{
		ThrustRight(Acceleration);
	} else
	{
		ThrustRight(Acceleration*(-1));
	}

	// TODO: add shooting behavior
}

void AEnemyShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   )
{
	//Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor && OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s collided with : %s"), *GetActorNameOrLabel(), *OtherActor->GetName());

		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			if (AMissile* MissileUFO = Cast<AMissile>(OtherUFO))
			{
				Health -= MissileUFO->DamagePower;
				MissileUFO->Destroy();
			}

			if (APlayerShip* PlayerUFO = Cast<APlayerShip>(OtherUFO))
			{
				Health -= PlayerUFO->DamagePower;
			}
		}
	}
}

void AEnemyShip::Init(int InHealth, int InScoreValue)
{
	MaxHealth = InHealth;
	Health = MaxHealth;
	ScoreValue = InScoreValue;
}

void AEnemyShip::Kill()
{
	AGameMaster* GM = Cast<AGameMaster>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameMaster::StaticClass()));
	if (GM)
	{
		GM->PlayerScore += ScoreValue;
		GM->BossAlive = false;
	}
	Super::Kill();
}
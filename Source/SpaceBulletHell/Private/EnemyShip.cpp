// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"
#include "EnemyMissile.h"
#include "GameMaster.h"
#include "Missile.h"
#include "PlayerShip.h"
#include "PlayerMissile.h"
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

	if (InvincibilityTimer > 0.f)
	{
		InvincibilityTimer -= DeltaTime;
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

	TimeSinceLastShot += DeltaTime;
	if (TimeSinceLastShot >= FireInterval)
	{
		FireProjectile();
		TimeSinceLastShot = 0.f;
	}
}

void AEnemyShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   )
{
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor && OtherActor != this && InvincibilityTimer <= 0.f && !ProjectilesTraites.Contains(OtherActor))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s collided with : %s"), *GetActorNameOrLabel(), *OtherActor->GetName());

		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			if (APlayerMissile* MissileUFO = Cast<APlayerMissile>(OtherUFO))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s is: %d"), *OtherActor->GetName(), MissileUFO->IsSpawnedByPlayer);
				if (MissileUFO->IsSpawnedByPlayer)
				{
					Health -= MissileUFO->DamagePower;
					MissileUFO->Destroy();
				}
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

void AEnemyShip::FireProjectile()
{
	ASpaceShip* Player = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player) return;

	FVector Forward = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	FVector SpawnLocation = GetActorLocation() + Forward * 1.f;

	// Angles en degrés pour les tirs
	float LeftAngle = -30.f;
	float RightAngle = 30.f;
	float RandomAngle = FMath::FRandRange(-20.f, 20.f);

	TArray<float> Angles = {LeftAngle, RandomAngle, RightAngle};

	for (float Angle : Angles)
	{
		// Calcul de la direction avec rotation autour de l'axe Z
		FRotator Rot = Forward.Rotation();
		Rot.Yaw += Angle;
		FVector Dir = Rot.Vector();

		FVector MissileInertia = Dir * 20.f;
		FRotator SpawnRotation = Dir.Rotation();
		FActorSpawnParameters SpawnParams;

		AEnemyMissile* NewMissile = GetWorld()->SpawnActor<AEnemyMissile>(EnemyMissileClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (NewMissile)
		{
			NewMissile->Init(MissileInertia, false);
			//UE_LOG(LogTemp, Warning, TEXT("EnemyShip FIRE Inertia: %s"), *MissileInertia.ToString());
		}
	}
}

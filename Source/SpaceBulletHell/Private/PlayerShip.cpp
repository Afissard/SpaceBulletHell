// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "Asteroid.h"
#include "EnemyShip.h"
#include "GameMaster.h"
#include "Missile.h"
#include "SpaceShip.h"
#include "Kismet/GameplayStatics.h"

APlayerShip::APlayerShip(): ASpaceShip()
{
	SphereCollision->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	
	// Game variables
	MaxHealth = 5;
	Health = MaxHealth;
	DamagePower = 0;
	ScoreValue = 0;

	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlayerShip::OnOverlap);
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShip::ThrustForward);
	PlayerInputComponent->BindAxis("ThrustRight", this, &APlayerShip::ThrustRight);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::FireProjectile);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::StartFireMissile);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerShip::StopFireMissile);
}


void APlayerShip::StartFireMissile()
{
	FireProjectile();
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &APlayerShip::FireProjectile, FireInterval, true);
}

void APlayerShip::StopFireMissile()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void APlayerShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor && OtherActor != this && InvincibilityTimer <= 0.f && !ProjectilesTraites.Contains(OtherActor))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s collided with : %s"), *GetActorNameOrLabel(), *OtherActor->GetName());

		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			if (AAsteroid* AsteroidUFO = Cast<AAsteroid>(OtherUFO))
			{
				Health -= AsteroidUFO->DamagePower;

				AGameMaster* GM = Cast<AGameMaster>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameMaster::StaticClass()));
				if (GM)
				{
					GM->PlayerScore += AsteroidUFO->ScoreValue;
				}
				
				AsteroidUFO->Kill();
			}

			if (AEnemyShip* EnemyShipUFO = Cast<AEnemyShip>(OtherUFO))
			{
				Health -= EnemyShipUFO->DamagePower;
			}
			if (AEnemyMissile* MissileUFO = Cast<AEnemyMissile>(OtherUFO))
			{
				Health -= MissileUFO->DamagePower;
				MissileUFO->Destroy();
			}
		}
	}
}

void APlayerShip::FireProjectile()
{
	ASpaceShip* Player = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player) return;

	FVector Forward = Player->GetActorForwardVector();
	FVector SpawnLocation = Player->GetActorLocation() + Forward * 75.f;

	FVector MissileInertia = FVector(1.f, 0.f, 0.f) * 20.f;

	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;

	APlayerMissile* NewMissile = GetWorld()->SpawnActor<APlayerMissile>(PlayerMissileClass, SpawnLocation, SpawnRotation, SpawnParams);
    if (NewMissile)
	{
		NewMissile->Init(MissileInertia, true);
	}
}
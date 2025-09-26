// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMaster.h"

#include "EnemyShip.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

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


	float TimeUntilNextBoss = 30.f - (TimeSinceLastBossRaid+(NumBossRaid+1%10)+(PlayerUpgrade+1%30));
	//UE_LOG(LogTemp, Warning, TEXT("BOSS RAID in %f seconds"), TimeUntilNextBoss);
	if (TimeUntilNextBoss <= 0.f && BossRaid == false && BossAlive == false)
	{
		BossRaid = true;
		TimeSinceLastBossRaid = 0.f;
	}

	if (BossRaid == false && BossAlive == false)
	{
		TimeSinceLastSpawn += DeltaTime;
		TimeSinceLastBossRaid += DeltaTime;
		if (TimeSinceLastSpawn >= 1.f) {
			for (int i=0; i<FMath::RandRange(0, SpawnRateAsteroid); i++)
			{
				spawnAsteroid();
			}
			TimeSinceLastSpawn = 0.f;
		}
	} else
	{
		// Destroy all asteroid
		for (TActorIterator<AAsteroid> It(GetWorld()); It; ++It)
		{
			AAsteroid* Asteroid = *It;
			if (Asteroid && !Asteroid->IsActorBeingDestroyed())
			{
				Asteroid->Kill();
			}
		}
		if (!BossAlive)
		{
			spawnBoss();
			BossRaid = false;
			BossAlive = true;
		}
	}
	
	PlayerUpgrade = PlayerScore / 100;
	
	if (PreviousPlayerUpgrade != PlayerUpgrade)
	{
		PreviousPlayerUpgrade = PlayerUpgrade;
		APlayerShip* Player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (Player)
		{
			Player->MaxHealth = 5 + PlayerUpgrade;
			Player->Health += 1;
		}
	}
}

void AGameMaster::spawnAsteroid()
{
	// Récupère la position du joueur
	APlayerShip* Player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player) return;

	FVector PlayerLocation = Player->GetActorLocation();

	// Choisit un angle aléatoire autour du joueur
	//	float Angle = FMath::RandRange(0.f, 2 * PI);
	float SpawnDistance = FMath::RandRange(2000.f, 2000.f); // Distance éloignée

	// Calcule la position de spawn autour du joueur
	float Angle = FMath::RandRange(-PI / 2, PI / 2); // De -90° à +90°
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
	FVector Inertia = Direction * Speed;

	// Game variables
	int MaxHealth = FMath::RandRange(1, 3);

	FRotator SpawnRotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);
	FActorSpawnParameters SpawnParams;
    //SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AAsteroid* NewAsteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (NewAsteroid)
	{
		NewAsteroid->Init(Inertia, MaxHealth);
	}
}

void AGameMaster::spawnBoss()
{
	NumBossRaid ++;
	
	FVector SpawnLocation = FVector(500.f, 0.f, 0.f);
	SetActorLocation(SpawnLocation);

	FRotator SpawnRotation = FRotator(0.f, 180, 0.f);
	FActorSpawnParameters SpawnParams;
	
	AEnemyShip* NewEnemyShip = GetWorld()->SpawnActor<AEnemyShip>(EnemyShipClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (NewEnemyShip)
	{
		int BossHealth = NumBossRaid*20;
		int BossScoreValue = NumBossRaid*100;
		NewEnemyShip->Init(BossHealth, BossScoreValue);

		//UE_LOG(LogTemp, Warning, TEXT("BOSS SPAWNED"));
	}
}
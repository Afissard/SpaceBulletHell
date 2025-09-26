// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "GameMaster.generated.h"

UCLASS()
class SPACEBULLETHELL_API AGameMaster : public AActor
{
	GENERATED_BODY()

	float TimeSinceLastSpawn = 0.f;
	float TimeSinceLastBossRaid = 0.f;
	
public:	
	// Sets default values for this actor's properties
	AGameMaster();

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	int SpawnRateAsteroid = 3; // Asteroid per second

	UPROPERTY(EditAnywhere, Category = "Asteroid")
	TSubclassOf<class AAsteroid> AsteroidClass;

	UPROPERTY(EditAnywhere, Category = "Boss")
	TSubclassOf<class AEnemyShip> EnemyShipClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int PlayerScore = 0;
	int PlayerUpgrade = 0;
	int PreviousPlayerUpgrade = PlayerUpgrade;

	UPROPERTY(BlueprintReadWrite, Category = "Game Rules")
	bool BossRaid = false;
	bool BossAlive = false;
	int NumBossRaid = 0;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void spawnAsteroid();

	void spawnBoss();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

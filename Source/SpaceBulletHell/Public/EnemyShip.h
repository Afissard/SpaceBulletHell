// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShip.h"
#include "EnemyMissile.h"
#include "EnemyShip.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API AEnemyShip : public ASpaceShip
{
	GENERATED_BODY()

	bool goRight = true;
	float TimeSinceLastShot = 0.f;
	

public:
	AEnemyShip();
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float FireInterval = 0.6f;
	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<AEnemyMissile> EnemyMissileClass;

	
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;

	void Init(int InHealth, int InScoreValue);

	void Kill() override;
	
	virtual void FireProjectile() override;
};

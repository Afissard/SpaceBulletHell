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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
	float FireInterval = 0.4f;
	float TimeSinceLastShot = 0.f;
	float Acceleration = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<AEnemyMissile> EnemyMissileClass;

public:
	AEnemyShip();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;

	void Init(int InHealth, int InScoreValue);

	void Kill() override;
	
	virtual void FireProjectile() override;
};

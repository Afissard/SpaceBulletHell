// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UFO.h"
#include "Missile.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API AMissile : public AUFO
{
	GENERATED_BODY()

public:
	bool IsSpawnedByPlayer;
	bool ToBeDestroyedNextFrame = false;
	
	void AMssile();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void Init(FVector newInertia, bool spawnedByPlayer);

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;
	};

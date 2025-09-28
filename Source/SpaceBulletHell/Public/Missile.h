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

	bool ToBeDestroyedNextFrame = false;

public:
	bool IsSpawnedByPlayer;
	
	void AMssile();
	
	virtual void Tick(float DeltaTime) override;

	void Init(FVector newInertia, bool spawnedByPlayer);

	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;
	};

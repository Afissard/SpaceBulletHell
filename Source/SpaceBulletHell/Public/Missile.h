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
	void AMssile();
	
	virtual void Tick(float DeltaTime) override;

	void Init(FVector newInertia);

	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;
	};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Missile.h"
#include "PlayerMissile.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API APlayerMissile : public AMissile
{
	GENERATED_BODY()

public:
	APlayerMissile();
	
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
				   bool bFromSweep, const FHitResult& SweepResult
				   ) override;
};

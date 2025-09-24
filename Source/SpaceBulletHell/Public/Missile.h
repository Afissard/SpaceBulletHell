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
	void AMssile();
	
	virtual void Tick(float DeltaTime) override;

	void Init(FVector newInertia);
	
};

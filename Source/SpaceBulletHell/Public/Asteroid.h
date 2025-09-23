// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UFO.h"
#include "Asteroid.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API AAsteroid : public AUFO
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};

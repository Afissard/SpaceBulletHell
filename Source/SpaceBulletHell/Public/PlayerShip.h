// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UFO.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBULLETHELL_API APlayerShip : public AUFO
{
	GENERATED_BODY()

	int PlayerScore = 0;
	
};

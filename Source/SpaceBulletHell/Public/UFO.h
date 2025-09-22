// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "UFO.generated.h"

UCLASS()
class SPACEBULLETHELL_API AUFO : public APawn
{
	GENERATED_BODY()

	// Game variables
	int Health = 1;
	int MaxHealth = 1;
	int ScoreValue = 0;
	int DamagePower = 1;

	// Movement variables
	FVector vTarget = FVector(0, 0, 0);
	FVector vPosition = FVector(0, 0, 0);
	FVector vVelocity = FVector(0, 0, 0);
	float dMaxSpeed = 10;

	// Hit box & mesh
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	

public:
	// Sets default values for this pawn's properties
	AUFO();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int GetDamagePower();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

	FVector Seek();

};

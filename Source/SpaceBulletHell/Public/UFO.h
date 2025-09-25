// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UFO.generated.h"

UCLASS()
class SPACEBULLETHELL_API AUFO : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUFO();

	// Hit box & mesh
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;

	// Game variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int Health = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int MaxHealth = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int ScoreValue = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int DamagePower = 1;

	// Movement variables
	FVector Inertia = FVector(0, 0, 0);
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComponent;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION()
	//void OnOverlap(AActor* MyActor, AActor* OtherActor);
	UFUNCTION()
    virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                   bool bFromSweep, const FHitResult& SweepResult
                   );
	

	//FVector Seek();

	void SpaceMovementApplyForce(const FVector ForceToApply);
};

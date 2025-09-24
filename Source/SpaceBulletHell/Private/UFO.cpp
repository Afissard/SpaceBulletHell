// Fill out your copyright notice in the Description page of Project Settings.


#include "UFO.h"

#include "PlayerShip.h"
#include "Components/SphereComponent.h"

// Sets default values
AUFO::AUFO()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// Hit box & mesh
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(SphereCollision);

	// Pour définir le sprite, utilisez un asset existant
	static ConstructorHelpers::FObjectFinderOptional<UPaperSprite> SpriteAsset(TEXT("/Game/Sprites/UFO_Sprite.UFO_Sprite"));
	if (SpriteAsset.Get())
	{
		SpriteComponent->SetSprite(SpriteAsset.Get());
	}
	
	SphereCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	
	// Movement
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AUFO::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AUFO::OnOverlap);	
}

int AUFO::GetDamagePower()
{
	return DamagePower;
}

// Called every frame
void AUFO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Out of bounds
	if (GetActorLocation().X < -5000.f ||
		GetActorLocation().X > 5000.f ||
		GetActorLocation().Y < -5000.f ||
		GetActorLocation().Y > 5000.f
		)
	{
		Destroy();
		return;
	}

	// Deatch check
	if (Health <= 0)
	{
		Destroy();
		return;
	}

}

// Called to bind functionality to input
void AUFO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUFO::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
					 bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision with : %s"), *OtherActor->GetName());

	if (OtherActor && OtherActor != this)
	{
		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			int OtherActorDamagePower = OtherUFO->GetDamagePower();
			Health -= OtherActorDamagePower;
			if (Health <= 0)
			{
				if (APlayerShip* PlayerUFO = Cast<APlayerShip>(OtherUFO))
				{
					PlayerUFO->ScoreValue += ScoreValue;
				}
				Destroy();
			}
		}
		else
		{
			Destroy();
		}
	}
}


/*
FVector AUFO::Seek()
{
	// 1. calculate the desired velocity
	FVector vDesired = vTarget - vPosition;
	// 2. normalize the desired velocity
	vDesired.Normalize();
	// 3. scale the desired velocity to the maximum speed
	vDesired *= dMaxSpeed;
	// 4. calculate the steering force
	FVector vSteering = vDesired - vVelocity;
	// 5. Limit Steering force to Max speed
	vSteering = vSteering.GetClampedToMaxSize(dMaxSpeed);
	vSteering.Z = 0.0f; // Keep movement in the XY plane
	return vSteering;
}
*/

void AUFO::SpaceMovementApplyForce(const FVector ForceToApply)
{
	// Applique la force uniquement sur X et Y
	Inertia.X += ForceToApply.X;
	Inertia.Y += ForceToApply.Y;
	Inertia.Z = 0.0f; // Pas de mouvement sur Z

	// Limite la vitesse maximale
	Inertia = Inertia.GetClampedToMaxSize(MovementComponent->MaxSpeed);

	// Applique l'inertie au mouvement
	MovementComponent->AddInputVector(Inertia);

	//UE_LOG(LogTemp, Warning, TEXT("%s (%s) inertia: %s"), *GetActorNameOrLabel(), *GetActorLocation().ToString(), *Inertia.ToString());
}
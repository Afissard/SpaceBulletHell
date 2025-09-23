// Fill out your copyright notice in the Description page of Project Settings.


#include "UFO.h"

#include "PlayerShip.h"
#include "Components/SphereComponent.h"

// Sets default values
AUFO::AUFO()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Hit box & mesh
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(SphereMesh.Object);
	}

	SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	SphereCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	// Movement
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AUFO::BeginPlay()
{
	Super::BeginPlay();
	
}

int AUFO::GetDamagePower()
{
	return DamagePower;
}

// Called every frame
void AUFO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO FIX: use the movement component
	FVector NewLocation = GetActorLocation() + Inertia * DeltaTime;
	NewLocation.Z = 0.f; // Reste dans le plan XY
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void AUFO::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUFO::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	// Check if the overlapping actor is valid and not itself
	if (OtherActor && (OtherActor != MyActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision avec : %s"), *OtherActor->GetName());
		
		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			int OtherActorDamagePower = OtherUFO->GetDamagePower();
			Health -= OtherActorDamagePower;
			if (Health <= 0)
			{
				if (APlayerShip* PlayerUFO = Cast<APlayerShip>(OtherUFO))
				{
					PlayerUFO->ScoreValue+=ScoreValue;
				}
				Destroy();
			}
		} else
		{
			// If anything else is touched then it mean it reach the world limit
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
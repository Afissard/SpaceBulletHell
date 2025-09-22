// Fill out your copyright notice in the Description page of Project Settings.


#include "UFO.h"
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

	FVector MoveDirection = Seek();
	AddMovementInput(MoveDirection, 1.0f);
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
		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			int OtherActorDamagePower = OtherUFO->GetDamagePower();
			Health -= OtherActorDamagePower;
			if (Health <= 0)
			{
				Destroy();
				// TODO add score to player if condition are met
			}
		}
	}
}

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
	vSteering.GetClampedToMaxSize(dMaxSpeed);
	vSteering.Z = 0.0f; // Keep movement in the XY plane
	return vSteering;
}
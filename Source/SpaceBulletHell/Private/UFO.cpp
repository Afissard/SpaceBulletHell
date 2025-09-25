// Fill out your copyright notice in the Description page of Project Settings.


#include "UFO.h"

#include "GameMaster.h"
#include "PlayerShip.h"
#include "Missile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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
	if (OtherActor && OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s collided with : %s"), *GetActorNameOrLabel(), *OtherActor->GetName());

		if (AUFO* OtherUFO = Cast<AUFO>(OtherActor))
		{
			
			AGameMaster* GM = Cast<AGameMaster>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameMaster::StaticClass()));
			if (GM)
			{
				if (APlayerShip* PlayerUFO = Cast<APlayerShip>(OtherUFO))
				{
					GM->PlayerScore += ScoreValue;
				}
				if (AMissile* MissileUFO = Cast<AMissile>(OtherUFO))
				{
					GM->PlayerScore += ScoreValue;
				}
			}
			
			Health -= OtherUFO->DamagePower;
			if (Health <= 0)
			{
				Destroy();
			}
		}
	}
}

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
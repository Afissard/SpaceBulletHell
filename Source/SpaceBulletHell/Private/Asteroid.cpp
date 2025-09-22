// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"

void AUFO::BeginPlay()
{
	Super::BeginPlay();

	// Set vTarget to a position behind the player (get a point around the player and trace a line and follow this
	// direction forever until it reach world end)
	APlayerShip* Player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		FVector PlayerForward = Player->GetActorForwardVector();
		// Position derrière le joueur, à une grande distance (par exemple 10000 unités)
		vTarget = PlayerLocation - PlayerForward * 10000.f;
	}
}

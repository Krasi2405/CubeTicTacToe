// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TicTacToePlayerController.h"


// Called when the game starts or when spawned
void ATicTacToePlayerController::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;

	cube = (ACube*) GetPawn();
	if (!cube) {
		UE_LOG(LogTemp, Error, TEXT("No cube controller by player controller!"))
	}
}

// Called every frame
void  ATicTacToePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


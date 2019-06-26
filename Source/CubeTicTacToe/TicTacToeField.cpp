// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacToeField.h"
#include "Square.h"
#include "TicTacToePlayerController.h"

// Sets default values
ATicTacToeField::ATicTacToeField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize neighbours of the 9 squares
	for (int i = 0; i <= 8; i++) {
		TArray<ATicTacToeField*>* Neighbours = new TArray<ATicTacToeField*>();
		if (i / 3 == 0) {
			Neighbours->Add(TopNeighbour);
		}
		else if (i / 3 == 2) {
			Neighbours->Add(BottomNeighbour);
		}

		if (i % 3 == 0) {
			Neighbours->Add(LeftNeighbour);
		}
		else if(i % 3 == 2)
		{
			Neighbours->Add(RightNeighbour);
		}

		if (Neighbours->Num() == 0) {
			Neighbours->Add(this);
		}
		AvailableFieldsMap.Add(i, Neighbours);
	}
}

// Called when the game starts or when spawned
void ATicTacToeField::BeginPlay()
{
	Super::BeginPlay();

	for (ASquare* Square : Squares) {
		Square->SetOwnerField(this);
	}
}

// Called every frame
void ATicTacToeField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATicTacToeField::AddSquare(ASquare* Square) {
	Squares.Add(Square);
}


void ATicTacToeField::DisableSquares() {
	if (!bSquaresDisabled) {
		for (ASquare* Square : Squares) {
			Square->Disable();
		}
		bSquaresDisabled = true;
	}
}


void ATicTacToeField::EnableSquares() {
	if (bSquaresDisabled) {
		for (ASquare* Square : Squares) {
			Square->Enable();
		}
		bSquaresDisabled = false;
	}
}


void ATicTacToeField::CheckSquare(ASquare* CheckedSquare, PlayerIndex PlayerIndex) {
	UE_LOG(LogTemp, Warning, TEXT("Check Square: %s"), (*CheckedSquare->GetName()))
	// UE_LOG(LogTemp, Warning, TEXT("Squares length: %d"), Squares.Num())
	// int SquareIndex = Squares.IndexOfByKey(Square);
	// TArray<ATicTacToeField*>** Neighbours = AvailableFieldsMap.Find(SquareIndex);

}


void ATicTacToeField::SetNeighbours(ATicTacToeField* Top, ATicTacToeField* Right, ATicTacToeField* Bottom, ATicTacToeField* Left) {
	//TopNeighbour = Top;
	//RightNeighbour = Right;
	//BottomNeighbour = Bottom;
	//LeftNeighbour = Left;
}
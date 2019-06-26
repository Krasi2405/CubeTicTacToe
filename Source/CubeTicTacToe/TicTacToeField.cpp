// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacToeField.h"
#include "Square.h"
#include "TicTacToePlayerController.h"

// Sets default values
ATicTacToeField::ATicTacToeField()
{
	
}

// Called when the game starts or when spawned
void ATicTacToeField::BeginPlay()
{
	Super::BeginPlay();
	if (!OwnerCube) {
		UE_LOG(LogTemp, Error, TEXT("Owner of tic tac toe field %s has not been set!"), *GetName());
		Destroy();
	}

	// Children have to be ordered correctly in blueprint in order for game to work correctly!
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors, false);
	for (AActor* ChildActor : ChildActors) {
		ASquare* Square = dynamic_cast<ASquare*>(ChildActor);
		if (Square) {
			Squares.Add(Square);
		}
	}

	for (ASquare* Square : Squares) {
		Square->SetOwnerField(this);
	}

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
		else if (i % 3 == 2)
		{
			Neighbours->Add(RightNeighbour);
		}

		if (Neighbours->Num() == 0) {
			Neighbours->Add(this);
		}
		AvailableFieldsMap.Add(i, Neighbours);
	}
}

// Called every frame
void ATicTacToeField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATicTacToeField::DisableSquares() {
	if (!bSquaresDisabled) {
		UE_LOG(LogTemp, Warning, TEXT("Disable squares!"))
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

	int SquareIndex = Squares.IndexOfByKey(CheckedSquare);
	UE_LOG(LogTemp, Warning, TEXT("Check Square: %s with index %d"), (*CheckedSquare->GetName()), SquareIndex)
	TArray<ATicTacToeField*>** Neighbours = AvailableFieldsMap.Find(SquareIndex);
	UE_LOG(LogTemp, Warning, TEXT("Neighbour count: %d"), (*Neighbours)->Num())


	for (int i = 0; i < (*Neighbours)->Num(); i++) {
		ATicTacToeField* Field = (**Neighbours)[i];
		if (Field) {
			UE_LOG(LogTemp, Warning, TEXT("Neighbour %d: %s"), i, (*Field->GetName()))
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Neighbour %d is nullptr!"), i)
		}
	}

	OwnerCube->SetAllowedInputFieds(**Neighbours);
}


void ATicTacToeField::SetNeighbours(ATicTacToeField* Top, ATicTacToeField* Right, ATicTacToeField* Bottom, ATicTacToeField* Left) {
	TopNeighbour = Top;
	RightNeighbour = Right;
	BottomNeighbour = Bottom;
	LeftNeighbour = Left;
}
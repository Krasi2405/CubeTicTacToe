// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacToeField.h"
#include "Square.h"
#include "TicTacToePlayerController.h"

// Sets default values
ATicTacToeField::ATicTacToeField()
{
	PlayerOwner = PlayerIndex::None;
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


void ATicTacToeField::CheckSquare(ASquare* CheckedSquare, PlayerIndex Player) {

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

	// OwnerCube->SetAllowedInputFieds(**Neighbours);

	if (CheckWinCondition(Player)) {
		if (Player == PlayerIndex::FirstPlayer) {
			CheckX();
		}
		else if (Player == PlayerIndex::SecondPlayer) 
		{
			CheckO();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Game developer is debil! Only players are allowed to win!"))
		}
	}
}


void ATicTacToeField::SetNeighbours(ATicTacToeField* Top, ATicTacToeField* Right, ATicTacToeField* Bottom, ATicTacToeField* Left) {
	TopNeighbour = Top;
	RightNeighbour = Right;
	BottomNeighbour = Bottom;
	LeftNeighbour = Left;
}


bool ATicTacToeField::CheckWinCondition(PlayerIndex Player) {
	if (CheckDiagonalsWinCondition(Player)) {
		return true;
	}
	// TODO: Maybe add support for more than 3 rows?
	for (int i = 0; i < 3; i++) {
		if (CheckRowWinCondition(i, Player) || CheckCollumnWinCondition(i, Player)) {
			return true;
		}
	}
	return false;
}



bool ATicTacToeField::CheckRowWinCondition(int row, PlayerIndex Player) {
	for (int i = 0; i < 3; i++) {
		if (!IsSquareOwnedByPlayer(GetSquareAtPosition(i, row), Player)) {
			return false;
		}
	}
	return true;
}


bool ATicTacToeField::CheckCollumnWinCondition(int collumn, PlayerIndex Player) {
	for (int i = 0; i < 3; i++) {
		if (!IsSquareOwnedByPlayer(GetSquareAtPosition(collumn, i), Player)) {
			return false;
		}
	}
	return true;
}

bool ATicTacToeField::CheckDiagonalsWinCondition(PlayerIndex Player) {
	bool bHasWonFirstDiagonal = 
		IsSquareOwnedByPlayer(Squares[0], Player) && 
		IsSquareOwnedByPlayer(Squares[4], Player) && 
		IsSquareOwnedByPlayer(Squares[8], Player);

	bool bHasWonSecondDiagonal =
		IsSquareOwnedByPlayer(Squares[2], Player) &&
		IsSquareOwnedByPlayer(Squares[4], Player) &&
		IsSquareOwnedByPlayer(Squares[6], Player);

	return bHasWonFirstDiagonal || bHasWonSecondDiagonal;
}


/*
[0] [1] [2]
[3] [4] [5]
[6] [7] [8]
*/
ASquare* ATicTacToeField::GetSquareAtPosition(int x, int y) {
	return Squares[x + y * 3];
}


bool ATicTacToeField::IsSquareOwnedByPlayer(ASquare* Square, PlayerIndex Player) {
	return Square->GetPlayerOwner() == Player;
}


void ATicTacToeField::CheckX() {
	verify(PlayerTwoColorPlane)

	UE_LOG(LogTemp, Warning, TEXT("Player X has won!"))
	Check(PlayerOneColorPlane, PlayerIndex::FirstPlayer);
}


void ATicTacToeField::CheckO() {
	verify(PlayerTwoColorPlane)

	UE_LOG(LogTemp, Warning, TEXT("Player O has won!"))
	Check(PlayerTwoColorPlane, PlayerIndex::SecondPlayer);
}


void ATicTacToeField::Check(UPrimitiveComponent* ColorPlane, PlayerIndex Player) {
	ColorPlane->SetVisibility(true);
	PlayerOwner = Player;
	for (ASquare* Square : Squares) {
		Square->Destroy();
	}
}


bool ATicTacToeField::FieldIsOwnedByPlayer() {
	return PlayerOwner != PlayerIndex::None;
}


void ATicTacToeField::SetPlayerOneColorPlane(UPrimitiveComponent* PlayerOneColorPlane) {
	this->PlayerOneColorPlane = PlayerOneColorPlane;
}


void ATicTacToeField::SetPlayerTwoColorPlane(UPrimitiveComponent* PlayerTwoColorPlane) {
	this->PlayerTwoColorPlane = PlayerTwoColorPlane;
}
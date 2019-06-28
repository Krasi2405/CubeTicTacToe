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

	checkf(OwnerCube != nullptr, TEXT("Owner of tic tac toe field %s has not been set!"))

	InitializeSquareChildren();
	InitializeSquareNeighbours();
}

// Called every frame
void ATicTacToeField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATicTacToeField::InitializeSquareNeighbours() {
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


void ATicTacToeField::InitializeSquareChildren() {
	// Children have to be ordered correctly in blueprint in order for game to work correctly!
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors, false);
	for (AActor* ChildActor : ChildActors) {
		ASquare* Square = dynamic_cast<ASquare*>(ChildActor);
		if (Square) {
			Square->SetOwnerField(this);
			Squares.Add(Square);
		}
	}
}


void ATicTacToeField::DisableSquares() {
	if (!bSquaresDisabled) {
		for (ASquare* Square : Squares) {
			Square->DisableInput();
		}
		bSquaresDisabled = true;
	}
}


void ATicTacToeField::EnableSquares() {
	if (bSquaresDisabled) {
		for (ASquare* Square : Squares) {
			Square->EnableInput();
		}
		bSquaresDisabled = false;
	}
}


void ATicTacToeField::MarkSquare(ASquare* CheckedSquare, PlayerIndex Player) {
	int SquareIndex = Squares.IndexOfByKey(CheckedSquare);
	UE_LOG(LogTemp, Warning, TEXT("Check Square: %s with index %d"), (*CheckedSquare->GetName()), SquareIndex)
	TArray<ATicTacToeField*>** Neighbours = AvailableFieldsMap.Find(SquareIndex);

	// OwnerCube->SetAllowedInputFieds(**Neighbours);

	if (CheckWinCondition(Player)) {
		check(Player != PlayerIndex::None)

		if (Player == PlayerIndex::FirstPlayer) {
			MarkX();
		}
		else if (Player == PlayerIndex::SecondPlayer) 
		{
			MarkO();
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


void ATicTacToeField::MarkX() {
	verify(PlayerTwoColorPlane)

	Mark(PlayerOneColorPlane, PlayerIndex::FirstPlayer);
}


void ATicTacToeField::MarkO() {
	verify(PlayerTwoColorPlane)

	Mark(PlayerTwoColorPlane, PlayerIndex::SecondPlayer);
}


void ATicTacToeField::Mark(UPrimitiveComponent* ColorPlane, PlayerIndex Player) {
	ColorPlane->SetVisibility(true);
	PlayerOwner = Player;
	for (ASquare* Square : Squares) {
		Square->Destroy();
	}
	OwnerCube->MarkField(this);
}

PlayerIndex ATicTacToeField::GetPlayerOwner() {
	return PlayerOwner;
}


void ATicTacToeField::SetPlayerOneColorPlane(UPrimitiveComponent* PlayerOneColorPlane) {
	this->PlayerOneColorPlane = PlayerOneColorPlane;
}


void ATicTacToeField::SetPlayerTwoColorPlane(UPrimitiveComponent* PlayerTwoColorPlane) {
	this->PlayerTwoColorPlane = PlayerTwoColorPlane;
}


ATicTacToeField* ATicTacToeField::GetNeighbourInDirection(NeighbourDirection Direction) {
	switch (Direction) {
		case NeighbourDirection::Top:
			return TopNeighbour;
		case NeighbourDirection::Right:
			return RightNeighbour;
		case NeighbourDirection::Bottom:
			return BottomNeighbour;
		case NeighbourDirection::Left:
			return LeftNeighbour;
		default:
			checkNoEntry();
			break;
	}
	return nullptr;
}
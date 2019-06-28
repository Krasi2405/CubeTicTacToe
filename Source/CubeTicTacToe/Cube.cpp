// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "Square.h"
#include "TicTacToeField.h"
#include "TicTacToePlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ACube::ACube()
{

}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();

	if (!CubePivot) {
		UE_LOG(LogTemp, Error, TEXT("Cube pivot should be set from blueprint!"))
		Destroy();
	}

	AddFields();
}


void ACube::AddFields() {
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors);
	for (AActor* ChildActor : ChildActors) {
		ATicTacToeField* Field = dynamic_cast<ATicTacToeField*>(ChildActor);
		if (Field) {
			Fields.Add(Field);
		}
	}
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACube::SetCubePivot(UPrimitiveComponent* CubePivot) {
	this->CubePivot = CubePivot;
}


void ACube::HorizontalMovement(float Value) {
	if (SelectedSquare) {
		return;
	}
	FRotator RelativeRotation = FRotator(0, Value, 0);
	CubePivot->AddWorldRotation(RelativeRotation);
}


void ACube::VerticalMovement(float Value) {
	if (SelectedSquare) {
		return;
	}
	FRotator RelativeRotation = FRotator(Value, 0, 0);
	CubePivot->AddWorldRotation(RelativeRotation);
}


void ACube::Press() {
	ASquare* Square = GetSquareAtMousePosition();
	if (Square && !Square->IsDisabled()) {
		SelectedSquare = Square;
	}
}


void ACube::Release() {
	if (!SelectedSquare || SelectedSquare != GetSquareAtMousePosition()) {
		SelectedSquare = nullptr;
		return;
	}

	if (bFirstTurn) {
		SelectedSquare->MarkX();
	}
	else
	{
		SelectedSquare->MarkO();
	}
	bFirstTurn = !bFirstTurn;
	SelectedSquare = nullptr;
}


ASquare* ACube::GetSquareAtMousePosition() {
	APlayerController* PlayerController = (APlayerController*)GetController();
	if (PlayerController) {
		float MouseX;
		float MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);
		FVector2D MousePosition = FVector2D(MouseX, MouseY);
		FHitResult HitResult;
		if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, false, HitResult)) {
			AActor* HitActor = HitResult.GetActor();
			ASquare* Square = dynamic_cast<ASquare*>(HitActor);
			return Square;
		}
	}
	return nullptr;
}


// Called to bind functionality to input
void ACube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent!"))

	if (PlayerInputComponent) {
		PlayerInputComponent->BindAxis("Horizontal", this, &ACube::HorizontalMovement);
		PlayerInputComponent->BindAxis("Vertical", this, &ACube::VerticalMovement);

		PlayerInputComponent->BindAction("Click", IE_Pressed, this, &ACube::Press);
		PlayerInputComponent->BindAction("Click", IE_Released, this, &ACube::Release);
	}
}


void ACube::SetAllowedInputFieds(TArray<ATicTacToeField*> AllowedFields) {
	for (ATicTacToeField* Field : Fields) {
		Field->DisableSquares();
	}

	for (ATicTacToeField* AllowedField : AllowedFields) {
		checkf(AllowedField != nullptr, TEXT("Nullptr allowed field given to cube!"));

		if (AllowedField) {
			AllowedField->EnableSquares();
		}
	}
}


void ACube::MarkField(ATicTacToeField* Field) {
	PlayerIndex FieldOwner = Field->GetPlayerOwner();
	if (HasWon(FieldOwner, Field)) {
		if (FieldOwner == PlayerIndex::FirstPlayer) {
			UE_LOG(LogTemp, Warning, TEXT("First Player won!"))
		}
		else if (FieldOwner == PlayerIndex::SecondPlayer)
		{
			UE_LOG(LogTemp, Warning, TEXT("Second Player won!"))
		}
	}
	CompletedFields += 1;
	if (CompletedFields >= Fields.Num()) {
		UE_LOG(LogTemp, Warning, TEXT("Draw!"))
	}
}


bool ACube::HasWon(PlayerIndex Player, ATicTacToeField* StartingField) {
	// AdjacentFieldsForWin - 1 because StartingField is counted towards them.
	return
		HasWonDirection(Player, StartingField, NeighbourDirection::Top, AdjacentFieldsForWin - 1) ||
		HasWonDirection(Player, StartingField, NeighbourDirection::Right, AdjacentFieldsForWin - 1) ||
		HasWonDirection(Player, StartingField, NeighbourDirection::Bottom, AdjacentFieldsForWin - 1) ||
		HasWonDirection(Player, StartingField, NeighbourDirection::Left, AdjacentFieldsForWin - 1);
}


bool ACube::HasWonDirection(PlayerIndex Player, ATicTacToeField* Field, NeighbourDirection Direction, int HopLimit) {
	check(Field->GetPlayerOwner() == Player)
	check(Field != nullptr)

	if (HopLimit <= 0) {
		return true;
	}

	ATicTacToeField* Neighbour = Field->GetNeighbourInDirection(Direction);
	if (Neighbour->GetPlayerOwner() == Player) {
		return HasWonDirection(Player, Neighbour, Direction, HopLimit - 1);
	}
	else
	{
		return false;
	}
}
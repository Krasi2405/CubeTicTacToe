// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cube.generated.h"

class ASquare;
class ATicTacToeField;
class ATicTacToeHUD;
enum class PlayerIndex;
enum class NeighbourDirection;



UCLASS()
class CUBETICTACTOE_API ACube : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACube();

	UFUNCTION(BlueprintCallable)
	void SetCubePivot(UPrimitiveComponent* CubePivot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* CubePivot;

	UPROPERTY(VisibleAnywhere)
	TArray<ATicTacToeField*> Fields = TArray<ATicTacToeField*>();
	
	UPROPERTY(VisibleAnywhere)
	ASquare* SelectedSquare = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetAllowedInputFieds(TArray<ATicTacToeField*> Fields);

	void MarkField(ATicTacToeField* Field);

private:
	ATicTacToeHUD* HUD;

	UPROPERTY(EditAnywhere)
	int AdjacentFieldsForWin = 3;

	void AddFields();

	void HorizontalMovement(float Value);
	void VerticalMovement(float Value);

	void Press();
	void Release();

	ASquare* GetSquareAtMousePosition();

	PlayerIndex PlayerTurn;

	bool HasWon(PlayerIndex Player, ATicTacToeField* StartingField);

	bool HasWonDirection(PlayerIndex Player, ATicTacToeField* Field, NeighbourDirection Direction, int HopLimit);

	int CompletedFields = 0;
};
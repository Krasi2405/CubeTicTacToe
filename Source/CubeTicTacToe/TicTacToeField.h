// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "TicTacToeField.generated.h"

class ASquare;
class ACube;
enum class PlayerIndex;

enum class NeighbourDirection {
	Top,
	Right,
	Bottom,
	Left
};

UCLASS()
class CUBETICTACTOE_API ATicTacToeField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATicTacToeField();




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Neighbours)
	void SetNeighbours(ATicTacToeField* Top, ATicTacToeField* Right, ATicTacToeField* Bottom, ATicTacToeField* Left);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Neighbours)
	ATicTacToeField* TopNeighbour = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Neighbours)
	ATicTacToeField* RightNeighbour = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Neighbours)
	ATicTacToeField* BottomNeighbour = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Neighbours)
	ATicTacToeField* LeftNeighbour = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fields)
	ACube* OwnerCube;

	UFUNCTION(BlueprintCallable)
	void SetPlayerOneColorPlane(UPrimitiveComponent* PlayerOneColorPlane);

	UFUNCTION(BlueprintCallable)
	void SetPlayerTwoColorPlane(UPrimitiveComponent* PlayerTwoColorPlane);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerColor)
	UPrimitiveComponent* PlayerOneColorPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerColor)
	UPrimitiveComponent* PlayerTwoColorPlane;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DisableSquares();

	void EnableSquares();

	void MarkSquare(ASquare* Square, PlayerIndex PlayerIndex);

	PlayerIndex GetPlayerOwner();

	ATicTacToeField* GetNeighbourInDirection(NeighbourDirection Direction);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<ASquare*> Squares = TArray<ASquare*>();

	// Maps index of square to available fields
	TMap<int, TArray<ATicTacToeField*>*> AvailableFieldsMap = TMap<int, TArray<ATicTacToeField*>*>();

	// For optimization purposes so squares are not enabled or disabled if they already are.
	bool bSquaresDisabled = false;

	PlayerIndex PlayerOwner;

	void InitializeSquareNeighbours();

	void InitializeSquareChildren();

	void MarkX();

	void MarkO();

	void Mark(UPrimitiveComponent* ColorPlane, PlayerIndex Player);

	bool CheckWinCondition(PlayerIndex Player);

	bool CheckRowWinCondition(int row, PlayerIndex Player);

	bool CheckCollumnWinCondition(int collumn, PlayerIndex Player);

	bool CheckDiagonalsWinCondition(PlayerIndex Player);

	bool IsSquareOwnedByPlayer(ASquare* Square, PlayerIndex Player);

	ASquare* GetSquareAtPosition(int x, int y);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacToeField.generated.h"

class ASquare;
enum class PlayerIndex;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DisableSquares();

	void EnableSquares();

	void CheckSquare(ASquare* Square, PlayerIndex PlayerIndex);

private:
	// For optimization purposes so squares are not enabled or disabled if they already are.
	bool bSquaresDisabled = false;

	UPROPERTY(VisibleAnywhere)
	TArray<ASquare*> Squares = TArray<ASquare*>();

	// Maps index of square to available fields
	TMap<int, TArray<ATicTacToeField*>*> AvailableFieldsMap = TMap<int, TArray<ATicTacToeField*>*>();


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cube.generated.h"

class ASquare;

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

	UPROPERTY(BlueprintReadOnly)
	UPrimitiveComponent* CubePivot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HorizontalMovement(float Value);
	void VerticalMovement(float Value);

	void Press();
	void Release();

	ASquare* GetSquareAtMousePosition();

	ASquare* SelectedSquare = nullptr;

	bool bFirstTurn = true;
};

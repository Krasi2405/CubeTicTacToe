// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Cube.h"

#include "TicTacToePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class CUBETICTACTOE_API ATicTacToePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	ACube* cube;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
};

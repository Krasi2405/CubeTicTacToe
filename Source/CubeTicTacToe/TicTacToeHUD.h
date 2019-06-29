// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TicTacToeHUD.generated.h"

enum class PlayerIndex;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerTurnChange, FString, TurnText);

/**
 * 
 */
UCLASS()
class CUBETICTACTOE_API ATicTacToeHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = PlayerTurn)
	FOnPlayerTurnChange ChangePlayerTurnText;

	void UpdatePlayerTurn(PlayerIndex Player);
	
};

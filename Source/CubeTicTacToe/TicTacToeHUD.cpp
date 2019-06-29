// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToeHUD.h"
#include "TicTacToePlayerController.h"


void ATicTacToeHUD::UpdatePlayerTurn(PlayerIndex Player) {
	if (Player == PlayerIndex::FirstPlayer) {
		ChangePlayerTurnText.Broadcast("X's turn!");
	}
	else
	{
		ChangePlayerTurnText.Broadcast("O's turn!");
	}
}
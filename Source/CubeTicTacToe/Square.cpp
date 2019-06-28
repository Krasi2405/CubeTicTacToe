// Fill out your copyright notice in the Description page of Project Settings.


#include "Square.h"
#include "TicTacToeField.h"
#include "TicTacToePlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ASquare::ASquare()
{
	PlayerOwner = PlayerIndex::None;
}

// Called when the game starts or when spawned
void ASquare::BeginPlay()
{
	Super::BeginPlay();

	check(SquareMesh != nullptr)
}

// Called every frame
void ASquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquare::SetSquareMesh(UPrimitiveComponent* SquarePrimitive) {
	SquareMesh = SquarePrimitive;
}


void ASquare::SetSquareMeshMaterial(UMaterialInterface* Material) {
	if (Material) {
		SquareMesh->SetMaterial(0, Material);
	}
}

void ASquare::MarkX() {
	Mark(PlayerIndex::FirstPlayer, PlayerOneMaterial);
}

void ASquare::MarkO() {
	Mark(PlayerIndex::SecondPlayer, PlayerTwoMaterial);
}


void ASquare::Mark(PlayerIndex Player, UMaterial* PlayerMaterial) {
	if (PlayerOwner != PlayerIndex::None) {
		UE_LOG(LogTemp, Error, TEXT("Attempting to set Square owner who is already set!"))
		return;
	}
	SetSquareMeshMaterial(PlayerMaterial);
	bDisabled = true;
	PlayerOwner = Player;
	OwnerField->MarkSquare(this, Player);
}


void ASquare::SetOwnerField(ATicTacToeField* Field) {
	OwnerField = Field;
}


void ASquare::DisableInput() {
	if (PlayerOwner == PlayerIndex::None && !bDisabled) {
		bDisabled = true;
		SetSquareMeshMaterial(DisabledMaterial);
	}
}


void ASquare::EnableInput() {
	if (PlayerOwner == PlayerIndex::None && bDisabled) {
		bDisabled = false;
		SetSquareMeshMaterial(EnabledMaterial);
	}
}


bool ASquare::IsDisabled() {
	return bDisabled;
}


PlayerIndex ASquare::GetPlayerOwner() {
	return PlayerOwner;
}